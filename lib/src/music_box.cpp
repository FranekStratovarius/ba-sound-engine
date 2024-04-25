#include "music_box.hpp"

namespace SoundEngine {
	MusicBox::MusicBox() {
		this->source = new Source();
		this->source->set_position(0.0, 1.0, 0.0);
		this->current_state = new MusicState(source, "assets/30 Golden Win (piano).ogg");
		this->current_state->start();
	}

	MusicBox::~MusicBox() {
		delete source;
		delete[] states;
	}

	void MusicBox::setPosition(
		float position_x, float position_y, float position_z
	) {
		this->source->set_position(position_x, position_y, position_z);
	}
}