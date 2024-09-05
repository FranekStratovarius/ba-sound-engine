#ifndef SOUNDENGINE_SOUND_HPP
#define SOUNDENGINE_SOUND_HPP

#include "AL/al.h"
#include "alhelpers.hpp"
#include "sndfile.h"

#include "source.hpp"

enum FormatType {
	Int16,
	Float,
	IMA4,
	MSADPCM
};

namespace SoundEngine {
	/**
	* sound
	*/
	class Sound {
		public:
			Sound(const char* filename, float period);
			~Sound();
			ALuint* getNextBuffer(int bufferctr);
			int getMaxBufferCtr();
		private:
			void *small_buffer;
			int frames_to_load;
			
			enum FormatType sample_format = Int16;
			ALint byteblockalign = 0;
			ALint splblockalign = 0;
			ALenum err, format;
			ALsizei num_bytes;
			SF_INFO sfinfo;
			void *membuf;
			unsigned int number_of_buffers = 2;
			ALuint buffers[2];

			unsigned int bufferswap = 0;

			unsigned long song_memory_size;
	};
}
#endif