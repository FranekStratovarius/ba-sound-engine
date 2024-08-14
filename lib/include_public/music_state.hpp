#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

#include "lua.hpp"

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
			MusicState* nextState;
			int table_ref;
			lua_State *L;
	};
}

#endif