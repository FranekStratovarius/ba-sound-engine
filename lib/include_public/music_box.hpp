#ifndef SOUNDENGINE_MUSIC_BOX_HPP
#define SOUNDENGINE_MUSIC_BOX_HPP

#include <vector>
#include <lua.hpp>
#include "export.hpp"

#include "music_state.hpp"
#include "source.hpp"

typedef struct {
	const char* name;
	double value;
} WorldVariable;

namespace SoundEngine {
	class __export MusicBox {
		public:
			MusicBox();
			~MusicBox();
			void update();
			void setPosition(
				float position_x,
				float position_y,
				float position_z
			);
			void setWorldVariable(WorldVariable variable);
			std::vector<WorldVariable> getWorldVariables();
		private:
			void unqueueBuffers();
			void queueBuffers(std::vector<ALuint*> buffers);
			void playSources();
			MusicState **states;
			// don't delete, this is a pointer to one elemet of this->states!
			MusicState *currentState;
			std::vector<Source*> sources;
			std::vector<bool> silenced_sources;
			lua_State *L;
	};
}

#endif