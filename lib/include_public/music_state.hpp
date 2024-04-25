#ifndef SOUNDENGINE_MUSIC_STATE_HPP
#define SOUNDENGINE_MUSIC_STATE_HPP

#include "sound.hpp"
#include "source.hpp"

namespace SoundEngine {
	class MusicState {
		public:
			MusicState(Source *source, const char* filename);
			~MusicState();
			void start();
		private:
			Sound *sound;
			// no ownership over the source!
			Source *source;
	};
}

#endif