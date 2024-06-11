#include <lua.h>
#include <stdexcept>
#include "se_helpers.hpp"

#include "music_state.hpp"

namespace SoundEngine {

	MusicState::MusicState(Source *source, lua_State *L, int table_ref) {
		this->source = source;
		this->L = L;
		this->table_ref = table_ref;

		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
		lua_getfield(L, -1, "track");
		const char* filename = lua_tostring(L, -1);
		lua_pop(L, 2);
		// printf("loading track: %s\n", filename);

		sound = new Sound(filename);
	}


	MusicState::~MusicState() {
		delete sound;
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
			sprintf(
				error,
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
		const char* node = luaL_checkstring(L, 1);
		bool active = lua_toboolean(L, 2);
		printf("set_layer: %s [%d %s]\n", node, active, active ? "true" : "false");
		return 0;
	}

	void MusicState::start() {
		source->pause();
		source->setBuffer(sound);
		source->play();
	}

	MusicState* MusicState::update(float delta_t) {
		// run update function from lua state
		lua_rawgeti(L, LUA_REGISTRYINDEX, table_ref);
		lua_getfield(L, -1, "update");
		lua_call(L, 0, 0);
		lua_pop(L, 1);
		return nextState ? nextState : this;
	}
}