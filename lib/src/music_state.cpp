#include "se_helpers.hpp"

#include "music_state.hpp"

namespace SoundEngine {
	MusicState::MusicState(Source *source, const char* filename) {
		this->source = source;
		sound = new Sound(filename);
	}

	MusicState::~MusicState() {
		delete sound;
	}

	void MusicState::start() {
		source->pause();
		source->setBuffer(sound);
		source->play();
	}

	MusicState* MusicState::update(float delta_t) {
		return this;
	}
}