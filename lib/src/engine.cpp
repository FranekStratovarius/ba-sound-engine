#include <stdexcept>

#include "AL/al.h"

#include "alhelpers.hpp"
#include "engine.hpp"

namespace SoundEngine {
	Engine::Engine() {
		// Initialize OpenAL.
		if(InitAL(0,0) != 0) {
			throw std::runtime_error("can't initialize openAL");
		}
		alDopplerFactor(30.0f);
	}

	Engine::~Engine() {
		CloseAL();
	}
}