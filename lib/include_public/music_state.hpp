#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

#include <unordered_map>
#include <lua.hpp>

#include "sound.hpp"
#include "source.hpp"

namespace SoundEngine {
	class MusicState {
		public:
			MusicState(lua_State *L, int table_ref);
			~MusicState();
			void start();
			ALuint* getNextBuffer();
			MusicState* update();
			int getNumberOfLayers();

			int nextNode(lua_State *L);
			int setLayer(lua_State *L);
		private:
			std::unordered_map<const char*, Sound> sounds;
			Sound *sound;
			MusicState* nextState;
			int table_ref;
			lua_State *L;
			float period;
			float current_time;
	};
}

#endif