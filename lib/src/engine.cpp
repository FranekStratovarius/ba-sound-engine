#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

#include "sndfile.h"

#include "AL/al.h"
#include "AL/alext.h"

#include "alhelpers.hpp"
#include "engine.hpp"

SoundEngine::Engine::Engine() {
	// Initialize OpenAL.
	if(InitAL(0,0) != 0) {
		throw std::runtime_error("can't initialize openAL");
	}
	alDopplerFactor(70.0f);
}

SoundEngine::Engine::~Engine() {
	CloseAL();
}