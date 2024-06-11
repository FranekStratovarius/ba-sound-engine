#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include "sound.hpp"
#include "source.hpp"

namespace SoundEngine {
	class MusicState {
		public:
			MusicState(Source *source, lua_State *L, int table_ref);
			~MusicState();
			virtual void start();
			virtual MusicState* update(float delta_t);

			int next_node(lua_State *L);
			int set_layer(lua_State *L);
		private:
			Sound *sound;
			// no ownership, don't delete!
			Source *source;
			MusicState* nextState = nullptr;
			int table_ref;
			lua_State *L;
	};
}

#endif