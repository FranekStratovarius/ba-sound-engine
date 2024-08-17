#include "music_box.hpp"
#include "music_state.hpp"
#include "music_transition.hpp"
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
		source = new Source();
		source->setPosition(0.0, 1.0, 0.0);

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
		lua_pushcfunction(L, &dispatch<&MusicState::next_node>);
		lua_setglobal(L, "next_node");
		lua_pushcfunction(L, &dispatch<&MusicState::set_layer>);
		lua_setglobal(L, "set_layer");

		lua_getglobal(L, "music_states");
		
		// initialize array of music states
		unsigned long length = lua_rawlen(L, -1);
		states = new MusicState*[length];

		// start traversing the table of music_states
		unsigned long counter = 0;
		lua_pushnil(L);
		while(lua_next(L, -2) != 0){
			printf("# next\n");
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
				source,
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

			counter++;
		}

		// start with first state
		lua_getglobal(L, "first_state");
		lua_call(L, 0, 1);
		printf("first_state: %p\n", lua_touserdata(L, -1));
		currentState = static_cast<MusicState*>(lua_touserdata(L, -1));
		// save pointer to class instance https://stackoverflow.com/a/32416597
		*static_cast<MusicState**>(lua_getextraspace(L)) = currentState;
		currentState->start();
	}

	MusicBox::~MusicBox() {
		delete source;
		delete[] states;
		// close lua state
		lua_close(L);
	}

	void MusicBox::update(float delta_t) {
		MusicState* newCurrentState = currentState->update(delta_t);
		if(currentState != newCurrentState) {
			// save pointer to class instance https://stackoverflow.com/a/32416597
			*static_cast<MusicState**>(lua_getextraspace(L)) = newCurrentState;
			currentState = newCurrentState;
			currentState->start();
		}
	}

	void MusicBox::setPosition(
		float position_x, float position_y, float position_z
	) {
		source->setPosition(position_x, position_y, position_z);
	}

	void MusicBox::setWorldVariable(WorldVariable variable) {
		printf("setting %s to %f\n", variable.name, variable.value);
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
}