#ifndef LUA_HELPERS_HPP
#define LUA_HELPERS_HPP

#include <lua.hpp>

void dumpstack (lua_State *L);
void print_value(lua_State* L, int idx);
void print_table(lua_State* L,int depth = 0);

#endif