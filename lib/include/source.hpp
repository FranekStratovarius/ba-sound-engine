#ifndef SOUNDENGINE_SOURCE_HPP
#define SOUNDENGINE_SOURCE_HPP

#include "AL/al.h"
#include "sound.hpp"

namespace SoundEngine {
	class Source {
		public:
			Source();
			Source(SoundEngine::Sound sound);
			~Source();
			/**
			* set position of source in world
			*/
			void set_position(
				float position_x,
				float position_y,
				float position_z
			);
			void set_buffer(SoundEngine::Sound sound);
			void play();
			void pause();
			void rewind();
			void setLooping(bool looping);
			void setMono(bool mono);
		private:
			ALuint source = 0;
	};
}
#endif