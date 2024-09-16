#include <cmath>
#include <cstddef>
#include <cstdio>
#include <lua.hpp>
#include <stdexcept>
#include "lua.h"
#include "se_helpers.hpp"
#include "AL/al.h"

#include "music_state.hpp"

namespace SoundEngine {

	MusicState::MusicState(lua_State *L, int table_ref) {
		this->nextState = nullptr;
		this->L = L;
		this->table_ref = table_ref;
		this->current_time = 0;

		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);

		lua_getfield(L, -1, "bpm");
		period = 60.0f/(float)lua_tonumber(L, -1);
		lua_pop(L, 1);

		// get list of layers
		lua_getfield(L, -1, "layers");
		// printf("isnil: %i\n", lua_isnil(L, -1));
		int number_of_layers = 0;
		if(lua_isnil(L, -1) != 1) {
			lua_pushnil(L);
			while(lua_next(L, -2) != 0){
				// printf("loading next layer\n");
				const char* key = lua_tostring(L, -2);
				// printf("key: %s\n", key);
				const char* filename = lua_tostring(L, -1);
				// printf("filename: %s\n", filename);
				// and load them
				Sound* sound = new Sound(filename, period);
				// put them into a hashmap
				sounds.push_back({
					true,
					sound
				});
				// printf("loaded %s silenced %i\n", key, number_of_layers == 0 ? false : true);
				sound_ids[key] = number_of_layers;
				number_of_layers++;
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);
		lua_pop(L, 1);

		bufferctr = 0;
		maxBufferctr = sounds[0].sound->getMaxBufferCtr();
	}

	MusicState::~MusicState() {
		for(ToggleableSound toggleable_sound: sounds) {
			delete toggleable_sound.sound;
		}
	}

	std::vector<ALuint*> MusicState::getNextBuffers() {
		std::vector<ALuint*> buffers;
		for(ToggleableSound toggleable_sound: sounds) {
			if(!toggleable_sound.silenced) {
				buffers.push_back(
					toggleable_sound.sound->getNextBuffer(bufferctr)
				);
			}
		}
		bufferctr = (bufferctr + 1) % maxBufferctr;
		return buffers;
	}

	void MusicState::init() {
		// run init function from lua state
		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
		lua_getfield(L, -1, "init");
		if(lua_isnil(L, -1) == 0) {
			lua_call(L, 0, 0);
		}
		lua_pop(L, 1);
	}

	MusicState* MusicState::update() {
		// run update function from lua state
		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
		lua_getfield(L, -1, "update");
		if(lua_isnil(L, -1) == 0) {
			lua_call(L, 0, 0);
		}
		lua_pop(L, 1);
		
		// clear nextState and current_time for reuse so this state is
		// later restarted fresh
		if (nextState != nullptr) {
			bufferctr = 0;
			MusicState *switcheroo = nextState;
			nextState = nullptr;
			current_time = 0;
			return switcheroo;
		} else {
			return this;
		}
	}

	void MusicState::exit() {
		// run exit function from lua state
		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
		lua_getfield(L, -1, "exit");
		if(!lua_isnil(L, -1)) {
			lua_call(L, 0, 0);
		}
		lua_pop(L, 1);
	}

	int MusicState::getNumberOfLayers() {
		return (int)sounds.size();
	}

	/*
		set next node from lua
	*/
	int MusicState::nextNode(lua_State *L) {
		if(!lua_islightuserdata(L, 1)) {
			lua_Debug ar;
			lua_getstack(L, 1, &ar);
			lua_getinfo(L, "nSl", &ar);
			int line = ar.currentline;

			char error[200];
			snprintf(
				error,
				200,
				"lua [%s] %i: value passed to next_node is no music state",
				ar.source,
				line
			);

			throw std::runtime_error(error);
		}

		nextState = static_cast<MusicState*>(lua_touserdata(L, 1));
		// printf("skip to next node: %p\n", nextState);
		return 0;
	}

	/*
		activate/deactivate stem layer from lua
	*/
	int MusicState::setLayer(lua_State *L) {
		const char* node = luaL_checkstring(L, 1);
		bool active = lua_toboolean(L, 2);
		// printf("set_layer: %s [%d %s]\n", node, active, active ? "true" : "false");
		sounds[sound_ids[node]].silenced = !active;
		return 0;
	}
}