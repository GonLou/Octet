////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Engine Class
//
// is where all the main game variables stand

namespace octet {
	namespace scene {
		class engine : public resource {
		public:
			int count_cubes;		// cubes counter
			int count_spheres;		// spheres counter
			int count_cylinders;	// cylinder counter
			int active_shape;		// indicates the shape goal
			boolean sound;			// state of sound connected/disconnected
			int lives;				// number of lives
			int ship_location;		// tracking the ship location
			int timer;				// internal clock
			int number_objects;		// total objects in game
			boolean game_start;		// state of game
			int points;				// points player
			int camera_orientation;	// keep the angle of camera
			int node_spaceship;		// holds the node of the spaceship
			int end_game_counter;	// timer counting to the end of game

			// Default Constructor
			//
			// where the game variables are initialized
			engine() { 
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
				this->points = 0;
				this->camera_orientation = 0;
				this->node_spaceship = 0;
				this->end_game_counter = 100;
			}

			// Destructor
			//
			// where the game variables are destroyed
			~engine(void) {
			}

			// set the number of cubes collected
			void set_cubes(int count_cubes) {
				this->count_cubes = count_cubes;
			}

			// set the number of spheres collected
			void set_spheres(int count_spheres) {
				this->count_spheres = count_spheres;
			}

			// set the number of cylinders collected
			void set_cylinders(int count_cylinders) {
				this->count_cylinders = count_cylinders;
			}

			// set the lives
			void set_lives(int lives) {
				this->lives = lives;
			}

			// turns sound on/off
			void set_sound(bool sound) {
				this->sound = sound;
			}

			// indicates the location of the ship for object collision calculus
			void set_ship_location(int ship_location) {
				this->ship_location = ship_location;
			}

			// set the shape to be collected
			void set_active_shape(int active_shape) {
				this->active_shape = active_shape;
			}

			// internal game clock
			void set_timer(int timer) {
				this->timer = timer;
			}

			// set the number of total game objects
			void set_number_objects(int number_objects) {
				this->number_objects = number_objects;
			}

			// set game to start/unstart (default)
			void set_game_start(bool game_start) {
				this->game_start = game_start;
			}

			// set the number of game points
			void set_points(int points) {
				this->points = points;
			}

			// set the current angle of camera
			void set_camera_orientation(int camera_orientation) {
				this->camera_orientation = camera_orientation;
			}

			// set the node to control spaceship
			void set_node_spaceship(int node_spaceship) {
				this->node_spaceship = node_spaceship;
			}

			// set a counter to end the game
			void set_end_game_counter(int end_game_counter) {
				this->end_game_counter = end_game_counter;
			}

			// get the number of cubes collected
			int get_cubes() {
				return this->count_cubes;
			}

			// get the number of spheres collected
			int get_spheres() {
				return this->count_spheres;
			}
			
			// get the number of cylinders collected
			int get_cylinders() {
				return this->count_cylinders;
			}

			// get the actual active shape to collect
			int get_active_shape() {
				return this->active_shape;
			}

			// display the active shape text
			string get_active_shape_text() {
				switch (get_active_shape()) {
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

			// get the number of actual lives
			int get_lives() {
				return this->lives;
			}

			// get the status of sound on/off
			boolean get_sound() {
				return this->sound;
			}

			// get the text from status of sound
			string get_sound_text() {
				if (sound)
					return "sound on [N]";
				else
					return "sound off [M]";
			}

			// get the ship location for object collision detection
			int get_ship_location() {
				return this->ship_location;
			}

			// get the internal timer of the game
			int get_timer() {
				return this->timer;
			}

			// get the total number of objects
			int get_number_objects() {
				return this->number_objects;
			}

			// converts the location of the ship into a range of 3 numbers
			// 1 - left
			// 2 - center
			// 3 - right
			int get_ship_location_transform() {
				if (this->get_ship_location() <= -4)
					return  1;
				else if (this->get_ship_location() >= 4)
					return 3;
				else
					return 2;
			}

			// get the status of the game if started or not
			boolean get_game_start() {
				return this->game_start;
			}

			// get the number os points of the player
			int get_points() {
				return this->points;
			}

			// get the angle od the camera
			int get_camera_orientation() {
				return this->camera_orientation;
			}

			// get the node of the ship object for control purposes
			int get_node_spaceship() {
				return this->node_spaceship;
			}

			// get the internal clock counter to the end of the game
			int get_end_game_counter() {
				return this->end_game_counter;
			}

			// increment cube shapes
			void inc_cubes() {
				this->count_cubes = this->count_cubes + 1;
			}

			// increment spheres shapes
			void inc_spheres() {
				this->count_spheres = this->count_spheres + 1;
			}

			// increment cylinders shapes
			void inc_cylinders() {
				this->count_cylinders = this->count_cylinders + 1;
			}

			// increment the location of the ship
			void inc_ship_location() {
				this->ship_location = this->ship_location + 1;
			}

			// increment the internal game clock
			void inc_timer() {
				this->timer = this->timer + 1;
			}

			// decrement the internal game clock
			void dec_ship_location() {
				this->ship_location = this->ship_location - 1;
			}

			// decrement lives
			void dec_lives() {
				this->lives = this->lives - 1;
			}

			// increment the shapes value 
			void process_shape(int o_shape) {
				switch (o_shape) {
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