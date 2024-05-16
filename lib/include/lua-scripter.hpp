extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace SoundEngine {
	class LuaScripter {
		public:
			LuaScripter();
		private:
			int status;
			lua_State *L;
	};
}