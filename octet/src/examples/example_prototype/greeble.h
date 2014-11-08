////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Greeble Class.
//

namespace octet {
	namespace scene {
		class greeble : public resource {
		public:
			int node_start;
			int node_end;
			int position;

			greeble() {
				this->node_start = 0;
				this->node_end = 0;
				this->position = 0;
			}

			greeble(int node_start, int node_end, int position) {
				this->node_start = node_start;
				this->node_end = node_end;
				this->position = position;
			}

			// destructor
			~greeble(void) {
			}

			// set
			void set_node_start(int node_start) {
				this->node_start = node_start;
			}

			void set_node_end(int node_end) {
				this->node_end = node_end;
			}

			void set_position(int position) {
				this->position = position;
			}

			// get
			int get_node_start() {
				return this->node_start;
			}

			int get_node_end() {
				return this->node_end;
			}

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

			// reset the position and starts again from the begining
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