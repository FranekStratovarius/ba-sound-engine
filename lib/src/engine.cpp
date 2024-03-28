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

	/*
	LoadAndPlaySound(
		"assets/01 Lich is Unbreakable (Expedition 1).ogg",
		10.0, 1.0, 0.0
	);
	LoadAndPlaySound(
		"assets/30 Golden Win (piano).ogg",
		0.0, 1.0, 0.0
	);
	*/

	// create listener
	ALfloat listenerPos[] = {0.0,0.0,0.0};
	ALfloat listenerOri[]={0.0,0.0,-1.0, 0.0,1.0,0.0};

	// Position ...
	alListenerfv(AL_POSITION,listenerPos);
	ALenum error;
	if ((error = alGetError()) != AL_NO_ERROR) {
		printf("alListenerfv POSITION : %i\n", error);
		throw std::runtime_error("can't get position of listener");
	}
	// Orientation ...
	alListenerfv(AL_ORIENTATION,listenerOri);
	if ((error = alGetError()) != AL_NO_ERROR) {
		printf("alListenerfv ORIENTATION : %i\n", error);
		throw std::runtime_error("can't get orientation of listener");
	}
}

SoundEngine::Engine::~Engine() {}