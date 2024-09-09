#include "music_box.hpp"
#include "music_state.hpp"
#include "music_transition.hpp"
#include "se_helpers.hpp"
#include "lua_helpers.hpp"
#include <cstdio>
#include <lua.h>
#include <stdexcept>

namespace SoundEngine {
	
	typedef int (MusicState::*mem_func)(lua_State * L);

	// This template wraps a member function into a C-style "free" function compatible with lua.
	template <mem_func func>
	int dispatch(lua_State * L) {
		MusicState * ptr = *static_cast<SoundEngine::MusicState**>(lua_getextraspace(L));
		return ((*ptr).*func)(L);
	}

	MusicBox::MusicBox() {
		int number_of_sources = 0;
		// source = new Source();
		// source->setPosition(0.0, 1.0, 0.0);

		L = luaL_newstate();
		if(!L) {
			throw std::runtime_error("can't initialize lua");
		}
		luaL_openlibs(L);
		int result = luaL_loadfile(L, "assets/states.lua");
		if(result != LUA_OK) {
			//error message
			char error[200];
			snprintf(error, 200, "could not load lua script: %s", lua_tostring(L, -1));
			throw std::runtime_error(error);
		} else {
			// of load was ok, execute the lua script
			int loadresult = lua_pcall(L, 0, LUA_MULTRET, 0);
			if(loadresult != LUA_OK) {
				char error[200];
				snprintf(error, 200, "could not execute lua script: %s", lua_tostring(L, -1));
				throw std::runtime_error(error);
			}
		}

		// create global table holding pointers to the music states
		lua_newtable(L);
		lua_setglobal(L, "states");

		// register c functions in lua
		lua_pushcfunction(L, &dispatch<&MusicState::nextNode>);
		lua_setglobal(L, "next_node");
		lua_pushcfunction(L, &dispatch<&MusicState::setLayer>);
		lua_setglobal(L, "set_layer");

		// get first state
		lua_getglobal(L, "first_state");
		const char* first_state = lua_tostring(L, -1);
		lua_pop(L, 1);

		lua_getglobal(L, "music_states");
		
		// initialize array of music states
		unsigned long length = (unsigned long)lua_rawlen(L, -1);
		states = new MusicState*[length];

		// start traversing the table of music_states
		unsigned long counter = 0;
		lua_pushnil(L);
		while(lua_next(L, -2) != 0){
			// printf("# next\n");
			if(!lua_istable(L, -1)) {
				char error[200];
				snprintf(
					error,
					200,
					"variable at position %lli is not a table.",
					lua_tointeger(L, -2)
				);
				throw std::runtime_error(error);
			}

			lua_getfield(L, -1, "name");
			const char* state_name = lua_tostring(L, -1);
			lua_pop(L, 1);
			// save reference to current table because this table holds all
			// the infos and code for this state
			int table_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			// create music state that calls the code in this table
			states[counter] = new MusicState(
				L,
				table_ref
			);

			lua_getglobal(L, "states");
			lua_pushstring(L, state_name);
			lua_pushlightuserdata(L, states[counter]); // value
			// settable pops both key and value
			lua_settable(L, -3);
			// pop the table music_states
			lua_pop(L, 1);
			// save first state
			if(state_name == first_state) {
				currentState = static_cast<MusicState*>(states[counter]);
			}

			int number_of_layers = states[counter]->getNumberOfLayers();
			if(number_of_layers > number_of_sources) {
				number_of_sources = number_of_layers;
			}

			counter++;
		}
		// save pointer to class instance https://stackoverflow.com/a/32416597
		*static_cast<MusicState**>(lua_getextraspace(L)) = currentState;

		// create sources for every possible layer
		for(int i = 0; i < number_of_sources; i++) {
			Source* source = new Source();
			source->setPosition(0.0, 1.0, 0.0);
			sources.push_back(source);
			silenced_sources.push_back(true);
		}

		// only load buffers of the first state
		currentState->init();
		std::vector<ALuint*> buffers = currentState->getNextBuffers();
		queueBuffers(buffers);
		buffers = currentState->getNextBuffers();
		queueBuffers(buffers);
		playSources();
	}

	MusicBox::~MusicBox() {
		delete[] states;
		// close lua state
		lua_close(L);
	}

	void MusicBox::update() {
		int buffers_processed = sources[0]->getBuffersProcessed();
		if(buffers_processed > 0) {
			MusicState* newCurrentState = currentState->update();
			if(currentState != newCurrentState) {
				// save pointer to class instance https://stackoverflow.com/a/32416597
				*static_cast<MusicState**>(lua_getextraspace(L)) = newCurrentState;
				currentState->exit();
				currentState = newCurrentState;
				currentState->init();
			}

			// source->unqueueBuffer();
			// ALuint* buffer = currentState->getNextBuffer();
			// source->queueBuffer(buffer);
			unqueueBuffers();
			std::vector<ALuint*> buffers = currentState->getNextBuffers();
			queueBuffers(buffers);
		}
	}

	void MusicBox::setPosition(
		float position_x, float position_y, float position_z
	) {
		for(Source* source: sources) {
			source->setPosition(position_x, position_y, position_z);
		}
	}

	void MusicBox::setWorldVariable(WorldVariable variable) {
		// printf("setting %s to %f\n", variable.name, variable.value);
		lua_getglobal(L, "world");
		lua_pushstring(L, variable.name);
		lua_pushnumber(L, variable.value);
		lua_settable(L, -3);
		lua_pop(L,-1);
	}

	std::vector<WorldVariable> MusicBox::getWorldVariables() {
		lua_getglobal(L, "world");
		std::vector<WorldVariable> variables;
		// iterate over table
		lua_pushnil(L);
		while(lua_next(L, -2) != 0){
			variables.push_back(
				WorldVariable {
					.name = lua_tostring(L, -2),
					.value = lua_tonumber(L, -1),
				}
			);
			lua_pop(L, 1);
		}
		return variables;
	}

	void MusicBox::unqueueBuffers() {
		// sources[0]->unqueueBuffer();
		for(Source* source: sources) {
			source->unqueueBuffer();
		}
	}

	void MusicBox::queueBuffers(std::vector<ALuint*> buffers) {
		size_t number_of_buffers = buffers.size();
		size_t number_of_sources = sources.size();
		// sources[0]->queueBuffer(buffers[0]);
		for(int i = 0; i < number_of_sources; i++) {
			// printf("queued buffer %i [%i]\n", i, i < number_of_buffers);
			sources[i]->silence(silenced_sources[i]);
			if(i < number_of_buffers) {
				// unsilence source and load next
				sources[i]->queueBuffer(buffers[i]);
				silenced_sources[i] = false;
			} else {
				// silence source and loop any buffer (buffer 0 is always there)
				sources[i]->queueBuffer(buffers[0]);
				silenced_sources[i] = true;
			}
		}
	}

	void MusicBox::playSources() {
		size_t number_of_sources = sources.size();
		ALuint *sources_ids = new ALuint[number_of_sources];
		for(int i = 0; i < number_of_sources; i++) {
			sources_ids[i] = sources[i]->getSource();
		}
		alSourcePlayv((ALsizei)number_of_sources, sources_ids);
		delete[] sources_ids;
	}
}