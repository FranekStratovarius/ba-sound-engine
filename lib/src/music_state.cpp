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

	MusicState::MusicState(Source *source, lua_State *L, int table_ref) {
		this->nextState = nullptr;
		this->source = source;
		this->L = L;
		this->table_ref = table_ref;
		this->current_time = 0;

		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);

		// get single track
		lua_getfield(L, -1, "track");
		const char* filename = lua_tostring(L, -1);
		lua_pop(L, 1);

		// get list of layers
		lua_getfield(L, -1, "layers");
		printf("isnil: %i\n", lua_isnil(L, -1));
		if(lua_isnil(L, -1) != 1) {
			lua_pushnil(L);
			while(lua_next(L, -2) != 0){
				printf("loading next layer\n");
				const char* key = lua_tostring(L, -2);
				printf("key: %s\n", key);
				const char* filename = lua_tostring(L, -1);
				printf("filename: %s\n", filename);
				// and load them
				Sound sound = Sound(filename, source->getSource());
				// put them into a hashmap
				sounds.insert({key, sound});
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);

		lua_getfield(L, -1, "bpm");
		period = 60.0/lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_pop(L, 1);
		printf("loading track: %s with %f\n", filename, period);

		sound = new Sound(filename, source->getSource());
	}

	MusicState::~MusicState() {
		delete sound;
	}

	void MusicState::start() {
		source->play();
	}

	void MusicState::loadBuffer() {
		sound->load_next_buffer();
	}

	void MusicState::swapBuffer() {
		sound->unload_previous_buffer();
		sound->load_next_buffer();
	}

	MusicState* MusicState::update() {
		int buffers_processed = source->getBuffersProcessed();
		// For each processed buffer, remove it from the source queue, read the next chunk of
		// audio data from the file, fill the buffer with new data, and add it to the source queue
		if(buffers_processed > 0) {
			// run update function from lua state
			lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
			lua_getfield(L, -1, "update");
			lua_call(L, 0, 0);
			lua_pop(L, 1);
		}
		// clear nextState and current_time for reuse so this state is
		// later restarted fresh
		if (nextState != nullptr) {
			sound->reset_track();
			MusicState *switcheroo = nextState;
			nextState = nullptr;
			current_time = 0;
			return switcheroo;
		} else {
			if (buffers_processed > 0) {
				sound->unload_previous_buffer();
				sound->load_next_buffer();
			}
			return this;
		}
	}

	int MusicState::getNumberOfLayers() {
		return sounds.size();
	}

	/*
		set next node from lua
	*/
	int MusicState::next_node(lua_State *L) {
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
		printf("skip to next node: %p\n", nextState);
		return 0;
	}

	/*
		activate/deactivate stem layer from lua
	*/
	int MusicState::set_layer(lua_State *L) {
		// const char* node = luaL_checkstring(L, 1);
		// bool active = lua_toboolean(L, 2);
		// printf("set_layer: %s [%d %s]\n", node, active, active ? "true" : "false");
		return 0;
	}
}