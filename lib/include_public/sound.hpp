#ifndef SOUNDENGINE_SOUND_HPP
#define SOUNDENGINE_SOUND_HPP

#include "AL/al.h"

namespace SoundEngine {
	/**
	* sound
	*/
	class Sound {
		public:
			Sound();
			Sound(const char* filename);
			~Sound();
			/**
			* loads the file into a buffer and saves the buffer-ID
			*/
			void load(const char* filename);
            ALuint getBuffer();
		private:
			ALuint buffer;
	};
}
#endif