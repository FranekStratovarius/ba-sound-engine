#ifndef SOUNDENGINE_HPP
#define SOUNDENGINE_HPP
#include <unordered_map>
#include "AL/alc.h"

namespace SoundEngine {
	/**
	* Hauptbestandteil der SoundEngine. Hier wird
	der Kontext von OpenAL gehalten
	* und geladene Sounds werden hier gespeichert.
	*
	* 
	*/
	class Engine {
		public:
			/// Erstellt eine Instanz der SoundEngine.
			Engine();

			/// Zerstört die Instanz der SoundEngine.
			~Engine();

			/**
			* Lädt Sounddatei von angegebenem Pfad
			* und spielt diese schnellstmöglich ab.
			*
			* @param filename Dateipfad der Sounddatei
			*/
			void play(const char* filename);

		private:
			std::unordered_map<const char*, int>
				loadedSounds;
			ALCcontext *context;
			ALCdevice *device;
	};
}
#endif