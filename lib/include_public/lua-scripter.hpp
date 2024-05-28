extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace SoundEngine {
	class LuaScripter {
		public:
			LuaScripter();
			~LuaScripter();
		private:
			int next_node(lua_State *L);
			int set_layer(lua_State *L);
			int status;
			lua_State *L;
	};
}