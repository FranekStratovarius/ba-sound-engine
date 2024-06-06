// #ifndef SOUNDENGINE_MUSIC_TRANSITION_HPP
// #define SOUNDENGINE_MUSIC_TRANSITION_HPP

// #include "music_state.hpp"

// namespace SoundEngine {
// 	class MusicTransition : public MusicState {
// 		public:
// 			MusicTransition(
// 				Source* source, const char* filename,
// 				MusicState *next, float duration
// 			);
// 			~MusicTransition();
// 			void start() override;
// 			MusicState* update(float delta_t) override;
// 		private:
// 			float duration;
// 			float elapsed;
// 			// no ownership, don't delete!
// 			MusicState *next;
// 	};
// }

// #endif