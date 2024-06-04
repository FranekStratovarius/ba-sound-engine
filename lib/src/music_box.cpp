#include "music_box.hpp"
#include "music_state.hpp"
#include "music_transition.hpp"
#include "lua_helpers.hpp"
#include <cstdio>
#include <lua.h>
#include <stdexcept>

namespace SoundEngine {
	MusicBox::MusicBox() {
		source = new Source();
		source->setPosition(0.0, 1.0, 0.0);

		L = luaL_newstate();
		if(!L) {
			throw std::runtime_error("can't initialize lua");
		}
		luaL_openlibs(L);
		// int result=luaL_loadfile(L,"assets/table.lua");
		int result = luaL_loadfile(L, "assets/states.lua");
		if(result != LUA_OK) {
			//fehlermeldung, danach sollte man ne fehlerbehandlung machen
			char error[200];
			sprintf(error, "Konnte Luascript nicht laden: %s", lua_tostring(L, -1));
			throw std::runtime_error(error);
		} else {
			//falls ok geladen luafile ausführen
			int loadresult = lua_pcall(L, 0, LUA_MULTRET, 0);
			if(loadresult != LUA_OK) {
				char error[200];
				sprintf(error, "Konnte Luascript nicht ausführen: %s", lua_tostring(L, -1));
				throw std::runtime_error(error);
			}
		}

		// create global world table
		lua_newtable(L);
		lua_setglobal(L, "world");

		// lua_pushcfunction(L, &dispatch<&MusicState::next_node>);
		// lua_setglobal(L, "next_node");
		// lua_pushcfunction(L, &dispatch<&MusicState::set_layer>);
		// lua_setglobal(L, "set_layer");

		setWorldVariable("enemy_count", 0);
		setWorldVariable("wonders", 0);

		lua_getglobal(L, "music_states");
		// lua_getfield(L, -1, "name");
		// const char* name = luaL_checkstring(L, 1);
		// printf("node name: %s\n", name);

		dumpstack(L);
		lua_pushnil(L);
		while(lua_next(L, -2) != 0){
			// printf("next\n");
			// dumpstack(L);
			print_value(L, -2);
			printf("=");
			//value ausgeben
			print_value(L, -1);
			printf(",\n");
			lua_pop(L, 1);
		}
		// print_table(L);

		states = new MusicState*[2];
		// states[0] = new MusicState(source, "assets/30 Golden Win (piano).ogg");
		// states[1] = new MusicTransition(
		// 	source, "assets/01 Lich is Unbreakable (Expedition 1).ogg",
		// 	states[0], 1.0
		// );

		// currentState = states[0];
		// // save pointer to class instance https://stackoverflow.com/a/32416597
		// *static_cast<MusicState**>(lua_getextraspace(L)) = currentState;
		// currentState->start();
	}

	MusicBox::~MusicBox() {
		delete source;
		delete[] states;
	}

	void MusicBox::update(float delta_t) {
		currentState = currentState->update(delta_t);
	}

	void MusicBox::setPosition(
		float position_x, float position_y, float position_z
	) {
		source->setPosition(position_x, position_y, position_z);
	}

	void MusicBox::setWorldVariable(const char* index, double value) {
		lua_getglobal(L, "world");
		lua_pushstring(L, index);
		lua_pushnumber(L, value);
		lua_settable(L, -3);
		lua_pop(L,-1);
	}
}