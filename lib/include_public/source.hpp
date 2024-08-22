#ifndef SOUNDENGINE_SOURCE_HPP
#define SOUNDENGINE_SOURCE_HPP

#include "AL/al.h"
#include "sound.hpp"

namespace SoundEngine {
	class Source {
		public:
			Source();
			Source(Sound sound);
			~Source();
			/**
			* set position of source in world
			*/
			void setPosition(
				float position_x = 0.0,
				float position_y = 0.0,
				float position_z = 0.0
			);
			void setBuffer(Sound *sound);
			void play();
			void pause();
			void rewind();
			void setLooping(bool looping);
			void setMono(bool mono);
		private:
			ALuint source;
	};
}
#endif