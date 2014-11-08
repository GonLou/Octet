////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Greeble Class
//
// is where all the city blocks are registered

namespace octet {
	namespace scene {
		class greeble : public resource {
		public:
			int node_start; // holds the first shape of a blocks group
			int node_end;	// holds the last shape of a blocks group
			int position;	// holds the position of the blocks group

			// Default Constructor
			//
			// where the block group is initialized
			greeble() {
				this->node_start = 0;
				this->node_end = 0;
				this->position = 0;
			}

			// Constructor
			//
			// where the block group is initialized
			greeble(int node_start, int node_end, int position) {
				this->node_start = node_start;
				this->node_end = node_end;
				this->position = position;
			}

			// Destructor
			//
			// where the block group is destroyed
			~greeble(void) {
			}

			// set the start node
			void set_node_start(int node_start) {
				this->node_start = node_start;
			}

			// set the end node
			void set_node_end(int node_end) {
				this->node_end = node_end;
			}

			// set the position of the block group
			void set_position(int position) {
				this->position = position;
			}

			// get the start node
			int get_node_start() {
				return this->node_start;
			}

			// get the end node
			int get_node_end() {
				return this->node_end;
			}

			// get the block group position
			int get_position() {
				return this->position;
			}

			// move the greebles
			void move(ref<visual_scene> app_scene) {
				for (int i = get_node_start(); i <= get_node_end(); i++) {
					scene_node *move = app_scene->get_mesh_instance(i)->get_node();
					move->translate(vec3(0.0f, 0.0f, 0.5f));
				}
				this->set_position(this->get_position()+1);
			}

			// reset the position and starts again from the begining creating a perpetuous moving
			void reset(ref<visual_scene> app_scene) {
				for (int i = get_node_start(); i <= get_node_end(); i++) {
					scene_node *move = app_scene->get_mesh_instance(i)->get_node();
					move->translate(vec3(0.0f, 0.0f, -125.0f));
				}
				this->set_position(0);
			}

		};
	}
}