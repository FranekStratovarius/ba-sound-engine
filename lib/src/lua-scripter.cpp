#include "lua-scripter.hpp"
#include <stdexcept>

SoundEngine::LuaScripter::LuaScripter() {
	L = luaL_newstate(); // open Lua
	if (!L) {
		throw std::runtime_error("can't initialize lua");
	}
}