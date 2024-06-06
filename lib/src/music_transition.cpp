// #include "music_transition.hpp"
// #include <cstdio>

// namespace SoundEngine {
// 	MusicTransition::MusicTransition(
// 		Source* source, const char* filename,
// 		MusicState *next, float duration
// 	) : MusicState(source, filename) {
// 		this->next = next;
// 		this->duration = duration;
// 	}

// 	void MusicTransition::start() {
// 		elapsed = 0;
// 		MusicState::start();
// 	}

// 	MusicState* MusicTransition::update(float delta_t) {
// 		elapsed += delta_t;
// 		printf("eapsed: %f\n", elapsed);
// 		if (elapsed >= duration) {
// 			next->start();
// 			return next;
// 		} else {
// 			return this;
// 		}
// 	}
// }