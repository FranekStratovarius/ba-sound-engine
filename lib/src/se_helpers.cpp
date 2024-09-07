#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "AL/al.h"
#include "se_helpers.hpp"

void checkAlError(const char* format) {
	ALenum error;
	if ((error = alGetError()) != AL_NO_ERROR) {
		char buffer[100];
		char error_string[30] = "";
		switch (error) {
			case AL_INVALID_NAME:
				strcpy_s(error_string, 30, "AL_INVALID_OPERATION");
			case AL_INVALID_ENUM:
				strcpy_s(error_string, 30, "AL_INVALID_ENUM");
			case AL_INVALID_VALUE:
				strcpy_s(error_string, 30, "AL_INVALID_VALUE");
			case AL_INVALID_OPERATION:
				strcpy_s(error_string, 30, "AL_INVALID_OPERATION");
			case AL_OUT_OF_MEMORY:
				strcpy_s(error_string, 30, "AL_OUT_OF_MEMORY");
			default:
				snprintf(error_string, 30, "%i", error);
		}
		printf(buffer, format, error_string);
		printf("OpenAL error: %s\n", alGetString(error));
		snprintf(buffer, 100, format, error_string);
		throw std::runtime_error(buffer);
	}
}