#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

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
	};
}

#endif