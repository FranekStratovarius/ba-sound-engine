#include "music_box.hpp"
#include "music_state.hpp"
#include "music_transition.hpp"

namespace SoundEngine {
	MusicBox::MusicBox() {
		source = new Source();
		source->setPosition(0.0, 1.0, 0.0);
		states = new MusicState*[2];
		states[0] = new MusicState(source, "assets/30 Golden Win (piano).ogg");
		states[1] = new MusicTransition(
			source, "assets/01 Lich is Unbreakable (Expedition 1).ogg",
			states[0], 1.0
		);
		currentState = states[1];
		currentState->start();
	}

	MusicBox::~MusicBox() {
		delete source;
		delete[] states;
	}

	void MusicBox::update(float delta_t) {
		currentState = currentState->update(delta_t);
	}

	void MusicBox::setPosition(
		float position_x, float position_y, float position_z
	) {
		source->setPosition(position_x, position_y, position_z);
	}
}