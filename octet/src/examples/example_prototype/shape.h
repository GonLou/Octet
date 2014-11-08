////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Shape Class
//
// is where all the game objects are registered

namespace octet {
	namespace scene {
		class shape : public resource {
		public:
			int line;			// keep the number of the vertical lane 1 / 2 / 3
			int position;		// position of the object
			int node;			// the node to control the object
			float speed;		// the speed of the object
			int time;			// the spawn time of the object
			int shape_type;		// indicates the shape type
			boolean is_alive;	// display if the object is still to be deployed or still at the screen
			int color;			// the color of the object

			// Default Constructor
			//
			// where the game objects are initialized
			shape(int color, int line, int node, int time, int shape_type) {
				this->color = color;
				this->line = line;
				this->position = 0;
				this->node = node;
				this->speed = 0.5f;
				this->time = time;
				this->shape_type = shape_type;
				this->is_alive = true;
			}

			// Destructor
			//
			// where the game objects are destroyed
			~shape(void) {
			}

			// set the lane of the object
			// 1 - left
			// 2 - center
			// 3 - right
			void set_line(int line) {
				this->line = line;
			}

			// set the position of the object
			void set_position(int pos) {
				this->position = pos;
			}

			// set the node of the object for control purposes
			void set_node(int node) {
				this->node = node;
			}

			// set the speed of the object
			void set_speed(float speed) {
				this->speed = speed;
			}

			// set the time to spawn the object
			void set_time(int time) {
				this->time = time;
			}

			// set the type of shape
			void set_shape_type(int shape_type) {
				this->shape_type = shape_type;
			}

			// set if the object is still valid or not
			void set_is_alive(int is_alive) {
				this->is_alive = is_alive;
			}

			// set the object color
			void set_color(int color) {
				this->color = color;
			}

			// get the lane of the object
			int get_line() {
				return this->line;
			}

			// get the node of the object for control purposes
			int get_node() {
				return this->node;
			}

			// get the position of the object
			int get_position() {
				return this->position;
			}

			// get the speed of the object
			float get_speed() {
				return this->speed;
			}

			// get the spawn time from the object
			int get_time() {
				return this->time;
			}

			// get the shape type
			int get_shape_type() {
				return this->shape_type;
			}

			// get tha value of the object if still is alive
			boolean get_is_alive() {
				return this->is_alive;
			}

			// get the color of the object
			int get_color() {
				return this->color;
			}

			// move all the game shapes
			void move(int node, ref<visual_scene> app_scene) {
				scene_node *move = app_scene->get_mesh_instance(node)->get_node();
				move->translate(vec3(0.0f, 0.0f, this->get_speed()));
				inc_position();
			}

			// when a shape is corrected collected deploys a reducer effect
			void fade(int node, ref<visual_scene> app_scene) {
				scene_node *move = app_scene->get_mesh_instance(node)->get_node();
				this->set_speed(5);
				move->translate(vec3(0.0f, 0.0f, this->get_speed()));
				move->scale(vec3(this->get_speed() / 50, this->get_speed() / 50, this->get_speed() / 50));
				inc_position();
			}

			// increment object position 
			void inc_position() {
				this->position = this->position + 1;
			}

			// decrement object position 
			void inc_speed() {
				this->speed = this->speed + 0.1f;
			}

		};
	}
}