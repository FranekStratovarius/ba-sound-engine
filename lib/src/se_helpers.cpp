#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "AL/al.h"
#include "se_helpers.hpp"

void checkAlError(const char* string) {
	ALenum error;
	if ((error = alGetError()) != AL_NO_ERROR) {
		printf("OpenAL error: %s\n", alGetString(error));
		switch (error) {
			case AL_INVALID_NAME:
				printf("AL_INVALID_OPERATION");
			case AL_INVALID_ENUM:
				printf("AL_INVALID_ENUM");
			case AL_INVALID_VALUE:
				printf("AL_INVALID_VALUE");
			case AL_INVALID_OPERATION:
				printf("AL_INVALID_OPERATION");
			case AL_OUT_OF_MEMORY:
				printf("AL_OUT_OF_MEMORY");
		}
		printf("%s\n", string);
		throw std::runtime_error("OpenAL error");
	}
}