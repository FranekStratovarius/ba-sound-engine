#include "lua.hpp"

namespace SoundEngine {
	class LuaScripter {
		public:
			LuaScripter();
			~LuaScripter();
		private:
			int next_node(lua_State *L);
			int set_layer(lua_State *L);
			lua_State *L;
	};
}