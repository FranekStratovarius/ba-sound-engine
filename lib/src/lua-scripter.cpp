#include "lua-scripter.hpp"
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include "lua_helpers.hpp"
#include <stdexcept>

void set_field(lua_State *L, const char *index, int value) {
	lua_pushstring(L, index);
	lua_pushnumber(L, value);
	lua_settable(L, -3);
}

int SoundEngine::LuaScripter::next_node(lua_State *L) {
// static int next_node(lua_State *L) {
	const char* node = luaL_checkstring(L, 1);
	printf("skip to next node: %s\n", node);
	return 0;
}

int SoundEngine::LuaScripter::set_layer(lua_State *L) {
	const char* node = luaL_checkstring(L, 1);
	bool active = lua_toboolean(L, 2);
	printf("set_layer: %s [%d %s]\n", node, active, active ? "true" : "false");
	return 0;
}

typedef int (SoundEngine::LuaScripter::*mem_func)(lua_State * L);

// This template wraps a member function into a C-style "free" function compatible with lua.
template <mem_func func>
int dispatch(lua_State * L) {
	SoundEngine::LuaScripter * ptr = *static_cast<SoundEngine::LuaScripter**>(lua_getextraspace(L));
	return ((*ptr).*func)(L);
}

// typedef int (SoundEngine::LuaScripter::*set_layer)(lua_State * L);

// // This template wraps a member function into a C-style "free" function compatible with lua.
// template <set_layer func>
// int dispatch(lua_State * L) {
// 	SoundEngine::LuaScripter * ptr = *static_cast<SoundEngine::LuaScripter**>(lua_getextraspace(L));
// 	return ((*ptr).*func)(L);
// }

SoundEngine::LuaScripter::LuaScripter() {
	// open Lua
	L = luaL_newstate();
	if(!L) {
		throw std::runtime_error("can't initialize lua");
	}
	// save pointer to class instance https://stackoverflow.com/a/32416597
	*static_cast<LuaScripter**>(lua_getextraspace(L)) = this;
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

	//in diesem beispiel wird der returnwert des scripts ausgegeben
	// if(lua_istable(L,-1)) {
	// 	printtable(L);
	// }

	// lua_pushcfunction(L, next_node);
	lua_pushcfunction(L, &dispatch<&LuaScripter::next_node>);
	lua_setglobal(L, "next_node");
	lua_pushcfunction(L, &dispatch<&LuaScripter::set_layer>);
	lua_setglobal(L, "set_layer");

	lua_newtable(L);
	set_field(L, "enemy_count", 2);
	set_field(L, "wonders", 3);

	lua_setglobal(L, "world");

	// lua_getglobal(L, "update");
	// lua_call(L, 0, 0);

	lua_getfield(L, -1, "update");
	lua_call(L, 0, 0);

	lua_getglobal(L, "world");
	print_table(L);
	lua_pop(L,-1);

	//************************
	//***funktion ausführen***
	//************************
	// //hier wird eine funktion ausgeführt die als globale variable angelegt wurde
	// lua_getglobal(L,"sum");
	// //erstes argument auf stack schieben
	// lua_pushnumber(L,4);
	// //zweites argument auf stack schieben
	// lua_pushnumber(L,6);
	// //funktion mi lua_State,2 übergabewerten und 1 rückgabewert aufrufen
	// lua_call(L,2,1);
	// //resultat von stack lesen
	// printf("summe: %f\n",lua_tonumber(L,-1));
	//wert vom stack kicken
	//lua_pop(L,-1);
}

SoundEngine::LuaScripter::~LuaScripter() {
	// close lua state
	lua_close(L);
}