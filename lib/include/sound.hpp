namespace SoundEngine {
	/**
	* Einzelner Soundeffekt mit optionaler Position.
	*/
	class Sound {
		public:
			Sound();
			~Sound();
			static void play(const char* filename);
		private:
	};
}