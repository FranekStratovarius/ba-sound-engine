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
			MusicState(Source *source, const char* filename);
			~MusicState();
			virtual void start();
			virtual MusicState* update(float delta_t);
		private:
			Sound *sound;
			// no ownership, don't delete!
			Source *source;
			MusicState* nextState = nullptr;
			lua_State *L;

			int next_node(lua_State *L);
			int set_layer(lua_State *L);
	};
}

#endif