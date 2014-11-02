////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Engine Class.
//

namespace octet {
	namespace scene {
		class engine : public resource {
		public:
			int count_cubes;
			int count_spheres;
			int count_cylinders;
			int active_shape;
			boolean sound;
			int lives;
			int ship_location;

			engine() // default constructor
			{
				count_cubes = 0;
				count_spheres = 0;
				count_cylinders = 0;
				active_shape = 1;
				sound = false;
				lives = 3;
				ship_location = 0;
			}

			// set
			void set_cubes(int count_cubes)
			{
				count_cubes = count_cubes;
			}

			void set_spheres(int count_spheres)
			{
				count_spheres = count_spheres;
			}

			void set_cylinders(int count_cylinders)
			{
				count_cylinders = count_cylinders;
			}

			void set_lives(int lives)
			{
				lives = lives;
			}

			void set_sound_on()
			{
				sound = true;
			}

			void set_sound_off()
			{
				sound = false;
			}

			void set_ship_location(int ship_location)
			{
				ship_location = ship_location;
			}

			void set_active_shape(int active_shape)
			{
				active_shape = active_shape;
			}
			// get
			int get_cubes()
			{
				return count_cubes;
			}

			int get_spheres()
			{
				return count_spheres;
			}

			int get_cylinders()
			{
				return count_cylinders;
			}

			int get_active_shape()
			{
				return active_shape;
			}

			string get_active_shape_text()
			{
				switch (get_active_shape())
				{
					case 1:
						return "Cube";
						break;
					case 2:
						return "Sphere";
						break;
					case 3:
						return "Cylinder";
						break;
				}
			}

			int get_lives()
			{
				return lives;
			}

			string get_sound()
			{
				if (sound)
					return "sound on [N]";
				else
					return "sound off [M]";
			}

			int get_ship_location()
			{
				return ship_location;
			}

			// increment shapes
			void inc_cubes()
			{
				count_cubes = count_cubes + 1;
			}

			void inc_spheres()
			{
				count_spheres = count_spheres + 1;
			}

			void inc_cylinders()
			{
				count_cylinders = count_cylinders + 1;
			}

			void inc_ship_location()
			{
				ship_location = ship_location + 1;
			}

			// decrement lives
			void dec_lives()
			{
				lives = lives - 1;
			}

			void dec_ship_location()
			{
				ship_location = ship_location - 1;
			}

		};
	}
}