#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

#include <unordered_map>
#include <lua.hpp>
#include <vector>

#include "sound.hpp"

typedef struct {
	bool silenced;
	SoundEngine::Sound* sound;
} ToggleableSound;

namespace SoundEngine {
	class MusicState {
		public:
			MusicState(lua_State *L, int table_ref);
			~MusicState();
			void start();
			std::vector<ALuint*> getNextBuffers();
			void init();
			MusicState* update();
			void exit();
			int getNumberOfLayers();

			int nextNode(lua_State *L);
			int setLayer(lua_State *L);
		private:
			int number_of_layers;
			std::vector<ToggleableSound> sounds;
			std::unordered_map<const char*, int> sound_ids;
			// don't delete
			MusicState* nextState;
			int table_ref;
			// don't delete
			lua_State *L;
			float period;
			float current_time;
			int bufferctr;
			int maxBufferctr;
	};
}

#endif