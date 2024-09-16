#ifndef SOUNDENGINE_HPP
#define SOUNDENGINE_HPP
#include <unordered_map>
#include "export.hpp"
#include "AL/alc.h"

namespace SoundEngine {
	/**
	* Hauptbestandteil der SoundEngine. Hier wird
	* der Kontext von OpenAL initialisiert und gehalten.
	*/
	class __export Engine {
		public:
			/// Erstellt eine Instanz der SoundEngine.
			Engine();

			/// Zerstört die Instanz der SoundEngine.
			~Engine();

		private:
			std::unordered_map<const char*, int>
				loadedSounds;
			ALCcontext *context;
			ALCdevice *device;
	};
}
#endif