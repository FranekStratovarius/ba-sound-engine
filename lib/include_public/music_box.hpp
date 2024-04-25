#ifndef SOUNDENGINE_MUSIC_BOX_HPP
#define SOUNDENGINE_MUSIC_BOX_HPP

#include "music_state.hpp"
#include "source.hpp"

namespace SoundEngine {
	class MusicBox {
		public:
			MusicBox();
			~MusicBox();
			void setPosition(
				float position_x,
				float position_y,
				float position_z
			);
		private:
			MusicState **states;
			MusicState *current_state;
			Source *source;
	};
}

#endif