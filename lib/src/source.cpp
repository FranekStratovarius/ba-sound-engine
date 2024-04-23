#include "se_helpers.hpp"
#include "source.hpp"

SoundEngine::Source::Source() {
	/* Create the source to play the sound with. */
	source = 0;
	alGenSources(1, &source);
	alSourcei(source, AL_LOOPING, AL_TRUE);
	checkAlError("SOURCE error: %s | Failed to setup sound source\n");
}

SoundEngine::Source::Source(SoundEngine::Sound sound) {
	/* Create the source to play the sound with. */
	alGetError();
	source = 0;
	alGenSources(1, &source);
	checkAlError("SOURCE error: %s | Failed to generate sound source\n");
	alSourcei(source, AL_BUFFER, (ALint)sound.getBuffer());
	checkAlError("SOURCE error: %s | Failed to set sound source buffer\n");
}

SoundEngine::Source::~Source() {
	alDeleteSources(1, &source);
}

void SoundEngine::Source::set_position(
	float position_x = 0.0, float position_y = 0.0, float position_z = 0.0
) {
	alGetError();
	ALfloat sourcePos[] = {position_x, position_y, position_z};
	alSourcefv(source, AL_POSITION, sourcePos);
	checkAlError("SOURCE error: %s | Failed to set sound source position\n");
}

void SoundEngine::Source::set_buffer(SoundEngine::Sound sound) {
	alGetError();
	alSourcei(source, AL_BUFFER, (ALint)sound.getBuffer());
	checkAlError("SOURCE error: %s | Failed to set sound source buffer\n");
}

void SoundEngine::Source::play() {
	alGetError();
	alSourcePlay(source);
	checkAlError("SOURCE error: %s | Failed to play sound source\n");
}

void SoundEngine::Source::pause() {
	alGetError();
	alSourcePause(source);
	checkAlError("SOURCE error: %s | Failed to pause sound source\n");
}

void SoundEngine::Source::rewind() {
	alGetError();
	alSourceRewind(source);
	checkAlError("SOURCE error: %s | Failed to rewind sound source\n");
}

void SoundEngine::Source::setLooping(bool looping) {
	alGetError();
	alSourcei(source, AL_LOOPING, looping);
	checkAlError("SOURCE error: %s | Failed to set sound source looping\n");
}

void SoundEngine::Source::setMono(bool mono) {
	alGetError();
    int al_mono_bool = mono ? AL_TRUE : AL_FALSE;
	alSourcei(source, AL_SOURCE_RELATIVE, al_mono_bool);
	checkAlError("SOURCE error: %s | Failed to set sound source mono\n");
}