#ifndef LUA_HELPERS_HPP
#define LUA_HELPERS_HPP

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

void dumpstack (lua_State *L);
void print_value(lua_State* L, int idx);
void print_table(lua_State* L,int depth = 0);

#endif