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
			int timer;
			int number_objects;
			boolean game_start;

			engine() // default constructor
			{
				this->count_cubes = 0;
				this->count_spheres = 0;
				this->count_cylinders = 0;
				this->active_shape = 1;
				this->sound = false;
				this->lives = 3;
				this->ship_location = 0;
				this->timer = 0;
				this->number_objects = 20;
				this->game_start = false;
			}

			// set
			void set_cubes(int count_cubes)
			{
				this->count_cubes = count_cubes;
			}

			void set_spheres(int count_spheres)
			{
				this->count_spheres = count_spheres;
			}

			void set_cylinders(int count_cylinders)
			{
				this->count_cylinders = count_cylinders;
			}

			void set_lives(int lives)
			{
				this->lives = lives;
			}

			void set_sound_on()
			{
				this->sound = true;
			}

			void set_sound_off()
			{
				this->sound = false;
			}

			void set_ship_location(int ship_location)
			{
				this->ship_location = ship_location;
			}

			void set_active_shape(int active_shape)
			{
				this->active_shape = active_shape;
			}

			void set_timer(int timer)
			{
				this->timer = timer;
			}

			void set_number_objects(int number_objects)
			{
				this->number_objects = number_objects;
			}

			void set_game_start(bool game_start)
			{
				this->game_start = game_start;
			}

			// get
			int get_cubes()
			{
				return this->count_cubes;
			}

			int get_spheres()
			{
				return this->count_spheres;
			}

			int get_cylinders()
			{
				return this->count_cylinders;
			}

			int get_active_shape()
			{
				return this->active_shape;
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
				return this->lives;
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
				return this->ship_location;
			}

			int get_timer()
			{
				return this->timer;
			}

			int get_number_objects()
			{
				return this->number_objects;
			}

			int get_ship_location_transform()
			{
				if (this->get_ship_location() <= -4)
					return  1;
				else if (this->get_ship_location() >= 4)
					return 3;
				else
					return 2;
			}

			boolean get_start_game()
			{
				return this->game_start;
			}

			// increment shapes
			void inc_cubes()
			{
				this->count_cubes = this->count_cubes + 1;
			}

			void inc_spheres()
			{
				this->count_spheres = this->count_spheres + 1;
			}

			void inc_cylinders()
			{
				this->count_cylinders = this->count_cylinders + 1;
			}

			void inc_ship_location()
			{
				this->ship_location = this->ship_location + 1;
			}

			void inc_timer()
			{
				this->timer = this->timer + 1;
			}

			// decrement lives
			void dec_lives()
			{
				this->lives = this->lives - 1;
			}

			void dec_ship_location()
			{
				this->ship_location = this->ship_location - 1;
			}

			// increment the shapes value if catch the correct shape
			void process_shape(int o_shape)
			{
				switch (o_shape)
				{
				case 1:
					inc_cubes();
					break;
				case 2:
					inc_spheres();
					break;
				case 3:
					inc_cylinders();
					break;
				}
			}

		};
	}
}