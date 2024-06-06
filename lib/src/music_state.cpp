#include <lua.h>
#include <stdexcept>
#include "se_helpers.hpp"
#include "lua_helpers.hpp"

#include "music_state.hpp"

namespace SoundEngine {

	typedef int (MusicState::*mem_func)(lua_State * L);

	// This template wraps a member function into a C-style "free" function compatible with lua.
	template <mem_func func>
	int dispatch(lua_State * L) {
		MusicState * ptr = *static_cast<SoundEngine::MusicState**>(lua_getextraspace(L));
		return ((*ptr).*func)(L);
	}

	/*
	MusicState::MusicState(Source *source, const char* filename) {
		this->source = source;
		sound = new Sound(filename);

		L = luaL_newstate();
		if(!L) {
			throw std::runtime_error("can't initialize lua");
		}
		// save pointer to class instance https://stackoverflow.com/a/32416597
		*static_cast<MusicState**>(lua_getextraspace(L)) = this;
		luaL_openlibs(L);
		// int result=luaL_loadfile(L,"assets/table.lua");
		int result = luaL_loadfile(L, "assets/peaceful.lua");
		if(result == LUA_OK) {
			//falls ok geladen luafile ausführen
			lua_pcall(L, 0, LUA_MULTRET, 0);
		} else {
			//fehlermeldung, danach sollte man ne fehlerbehandlung machen
			throw std::runtime_error("Konnte Luascript nicht laden");
		}

		// create global world table
		lua_newtable(L);
		lua_setglobal(L, "world");

		lua_pushcfunction(L, &dispatch<&MusicState::next_node>);
		lua_setglobal(L, "next_node");
		lua_pushcfunction(L, &dispatch<&MusicState::set_layer>);
		lua_setglobal(L, "set_layer");

		// setWorldVariable("enemy_count", 0);
		// setWorldVariable("wonders", 0);

		dumpstack(L);
		// print_table(L);

		// lua_getfield(L, -1, "name");
		// const char* name = luaL_checkstring(L, 1);
		// printf("node name: %s\n", name);
	}
	*/

	MusicState::MusicState(Source *source, lua_State *L, int table_ref) {
		this->source = source;
		this->L = L;
		this->table_ref = table_ref;
	}


	MusicState::~MusicState() {
		delete sound;
		// close lua state
		lua_close(L);
	}

	/*
		set next node from lua
	*/
	int MusicState::next_node(lua_State *L) {
	// static int next_node(lua_State *L) {
		// const char* node = luaL_checkstring(L, 1);
		nextState = static_cast<MusicState*>(lua_touserdata(L, 1));
		// printf("skip to next node: %s\n", node);
		// TODO: find next MusicState by name
		// nextState = getMusicState(node);
		// nextState = node;
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
		dumpstack(L);
		lua_getfield(L, -1, "update");
		dumpstack(L);
		lua_call(L, 0, 0);
		return nextState ? nextState : this;
	}
}