#include "se_helpers.hpp"

#include "music_state.hpp"

namespace SoundEngine {
	MusicState::MusicState(Source *source, const char* filename) {
		this->source = source;
		this->sound = new Sound(filename);
		this->source->set_buffer(this->sound);
		this->source->setLooping(true);
	}

	MusicState::~MusicState() {
		delete this->sound;
	}

	void MusicState::start() {
		source->pause();
		source->set_buffer(this->sound);
		source->play();
	}
}