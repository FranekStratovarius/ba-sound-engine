#ifndef SOUNDENGINE_LISTENER_HPP
#define SOUNDENGINE_LISTENER_HPP

namespace SoundEngine {
	class Listener {
		public:
			Listener();
			void update(
				float position_x,
				float position_y,
				float position_z,
				float velocity_x,
				float velocity_y,
				float velocity_z,
				float look_at_x,
				float look_at_y,
				float look_at_z,
				float up_x,
				float up_y,
				float up_z
			);
			void setPosition(float x, float y, float z);
			void setVelocity(
				float velocity_x,
				float velocity_y,
				float velocity_z
			);
			void setOrientation(
				float look_at_x,
				float look_at_y,
				float look_at_z,
				float up_x,
				float up_y,
				float up_z
			);
		private:
	};
}
#endif