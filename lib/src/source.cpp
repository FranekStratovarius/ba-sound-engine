#include "AL/al.h"
#include "se_helpers.hpp"
#include "source.hpp"
#include <cstdio>

namespace SoundEngine {
	Source::Source() {
		/* Create the source to play the sound with. */
		source = 0;
		alGenSources(1, &source);
		checkAlError("SOURCE error: %s | Failed to setup sound source\n");
	}

	Source::~Source() {
		alDeleteSources(1, &source);
	}

	ALuint Source::getSource() {
		return source;
	}

	void Source::setPosition(
		float position_x, float position_y, float position_z
	) {
		alGetError();
		ALfloat sourcePos[] = {position_x, position_y, position_z};
		alSourcefv(source, AL_POSITION, sourcePos);
		checkAlError("SOURCE error: %s | Failed to set sound source position\n");
	}
	
	void Source::queueBuffer(ALuint* buffer) {
		alGetError();
		alSourceQueueBuffers(source, 1, buffer);
		checkAlError("SOURCE error: %s | Failed to queue buffer\n");
	}

	void Source::unqueueBuffer() {
		alGetError();
		ALuint uiBuffer = 0;
		alSourceUnqueueBuffers(source, 1, &uiBuffer);
		// printf("unloaded buffer: %i\n", uiBuffer);
		checkAlError("SOURCE error: %s | Failed to unload buffer\n");
	}

	int Source::getBuffersProcessed() {
		int buffers_processed = 0;
		alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffers_processed);
		return buffers_processed;
	}

	void Source::play() {
		alGetError();
		alSourcePlay(source);
		checkAlError("SOURCE error: %s | Failed to play sound source\n");
	}

	void Source::pause() {
		alGetError();
		alSourcePause(source);
		checkAlError("SOURCE error: %s | Failed to pause sound source\n");
	}

	void Source::rewind() {
		alGetError();
		alSourceRewind(source);
		checkAlError("SOURCE error: %s | Failed to rewind sound source\n");
	}

	void Source::silence(bool silence) {
		alSourcef(
			source,
			AL_GAIN,
			silence ? 0.0f : 1.0f
		);
	}

	void Source::setMono(bool mono) {
		alGetError();
		int al_mono_bool = mono ? AL_TRUE : AL_FALSE;
		alSourcei(source, AL_SOURCE_RELATIVE, al_mono_bool);
		checkAlError("SOURCE error: %s | Failed to set sound source mono\n");
	}
}