#include "AL/al.h"
#include "se_helpers.hpp"
#include "listener.hpp"

namespace SoundEngine {
	Listener::Listener() {
		setPosition(0.0, 0.0, 0.0);
		setOrientation(0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
	}

	void Listener::update(
		float position_x, float position_y, float position_z,
		float velocity_x, float velocity_y, float velocity_z,
		float look_at_x, float look_at_y, float look_at_z,
		float up_x, float up_y, float up_z
	) {
		setPosition(position_x, position_y, position_z);
		setVelocity(velocity_x, velocity_y, velocity_z);
		setOrientation(
			look_at_x, look_at_y, look_at_z,
			up_x, up_y, up_z
		);
	}

	void Listener::setPosition(
		float position_x = 0.0, float position_y = 0.0, float position_z = 0.0
	) {
		ALfloat listenerPos[] = {position_x, position_y, position_z};
		alListenerfv(AL_POSITION,listenerPos);
		// checkAlError("alListenerfv POSITION : %i | can't set position\n");
	}


	void Listener::setVelocity(
		float velocity_x,
		float velocity_y,
		float velocity_z
	) {
		ALfloat listenerVel[] = {velocity_x, velocity_y, velocity_z};
		alListenerfv(AL_VELOCITY, listenerVel);
		// checkAlError("alListenerfv ORIENTATION : %i | can't set velocity\n");
	}

	void Listener::setOrientation(
		float look_at_x, float look_at_y, float look_at_z,
		float up_x, float up_y, float up_z
	) {
		ALfloat listenerOri[]={
			look_at_x, look_at_y, look_at_z,
			up_x, up_y, up_z
		};
		alListenerfv(AL_ORIENTATION,listenerOri);
		// checkAlError("alListenerfv ORIENTATION : %i | can't set orientation\n");
	}
}