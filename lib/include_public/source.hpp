#ifndef SOUNDENGINE_SOURCE_HPP
#define SOUNDENGINE_SOURCE_HPP

#include "AL/al.h"

namespace SoundEngine {
	class Source {
		public:
			Source();
			~Source();
			ALuint getSource();
			/**
			* set position of source in world
			*/
			void setPosition(
				float position_x = 0.0,
				float position_y = 0.0,
				float position_z = 0.0
			);
			// void setBuffer(Sound *sound);
			void queueBuffer(ALuint* buffer);
			void unqueueBuffer();
			int getBuffersProcessed();
			void play();
			void pause();
			void rewind();
			void silence(bool silence);
			// ignore the spatial position of the source
			void setMono(bool mono);
		private:
			ALuint source;
	};
}
#endif