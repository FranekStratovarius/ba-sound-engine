#ifndef SOUNDENGINE_MUSIC_BOX_HPP
#define SOUNDENGINE_MUSIC_BOX_HPP

#include "lua.hpp"

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
			void setWorldVariable(const char* index, double value);
		private:
			MusicState **states;
			// don't delete, this is a pointer to one elemet of this->states!
			MusicState *currentState;
			Source *source;
			lua_State *L;
	};
}

#endif