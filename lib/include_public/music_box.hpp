#ifndef SOUNDENGINE_MUSIC_BOX_HPP
#define SOUNDENGINE_MUSIC_BOX_HPP

#include "music_state.hpp"
#include "source.hpp"

namespace SoundEngine {
	class MusicBox {
		public:
			MusicBox();
			~MusicBox();
			void update(float delta_t);
			void setPosition(
				float position_x,
				float position_y,
				float position_z
			);
		private:
			MusicState **states;
			// don't delete, this is a pointer to one elemet of this->states!
			MusicState *currentState;
			Source *source;
	};
}

#endif