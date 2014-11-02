namespace octet {
	namespace scene {
		class play_sound : public resource {

		public:
			play_sound(char * filename);
			~play_sound();

		private:
			char * buffer;
			bool ok;
			HINSTANCE HInstance;
		};

		play_sound::play_sound(char * filename)
		{
			ok = false;
			buffer = 0;
			HInstance = GetModuleHandle(0);

			ifstream infile(filename, ios::binary);

			if (!infile)
			{
				std::cout << "play_sound:: there is a file error: " << filename << std::endl;
				return;
			}

			infile.seekg(0, ios::end);   // get length of file
			int length = infile.tellg();
			buffer = new char[length];    // allocate memory
			infile.seekg(0, ios::beg);   // position to start of file
			infile.read(buffer, length);  // read entire file

			infile.close();
			ok = true;
		}

		play_sound::~play_sound() // destructor of playing sound
		{
			PlaySound(NULL, 0, 0); // stop sound
			delete[] buffer;      // delete buffer.
		}

		void play_sound::play(bool loop) // play the sound if sucessly loaded
		{
			if (!ok)
				return;

			if (loop)
				PlaySound(buffer, HInstance, SND_LOOP | SND_ASYNC);
			else
				PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC);
		}
	}
}