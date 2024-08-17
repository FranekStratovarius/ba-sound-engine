#ifndef SOUNDENGINE_MUSIC_BOX_HPP
#define SOUNDENGINE_MUSIC_BOX_HPP

#include <vector>
#include <lua.hpp>

#include "music_state.hpp"
#include "source.hpp"

typedef struct {
	const char* name;
	double value;
} WorldVariable;

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
			void setWorldVariable(WorldVariable variable);
			std::vector<WorldVariable> getWorldVariables();
		private:
			MusicState **states;
			// don't delete, this is a pointer to one elemet of this->states!
			MusicState *currentState;
			Source *source;
			lua_State *L;
	};
}

#endif