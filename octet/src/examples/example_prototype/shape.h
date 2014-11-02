////////////////////////////////////////////////////////////////////////////////
//
// Goncalo Lourenco 2014
//
// Shape Class.
//

namespace octet {
	namespace scene {
		class shape : public resource {
		public:
			int line;
			int position;
			int node;
			float speed;
			int time;

			shape() //default constructor starts at middle line
			{
				line = 2;
				position = 0;
				node = 0;
				speed = 0.02f;
				time = rand() % 110 + 1;
			}

			shape(int line, int position, int node, int time)
			{
				this->line = line;
				this->position = position;
				this->node = node;
				this->speed = 0.02f;
				this->time = time;
			}

			// set
			void set_line(int line)
			{
				this->line = line;
			}

			void set_position(int pos)
			{
				this->position = pos;
			}

			void set_node(int node)
			{
				this->node = node;
			}

			void set_speed(int speed)
			{
				this->speed = speed;
			}

			void set_time(int time)
			{
				this->time = time;
			}

			// get
			int get_line()
			{
				return line;
			}

			int get_node()
			{
				return node;
			}

			int get_position()
			{
				return position;
			}

			int get_speed()
			{
				return speed;
			}

			int get_time()
			{
				return time;
			}

			// move the shapes
			void move(int node, ref<visual_scene> app_scene)
			{
				scene_node *move = app_scene->get_mesh_instance(node)->get_node();
				//move->translate(vec3(0, 0, this->get_speed()));
				move->translate(vec3(0, 0, 0.5f));
				inc_position();
			}

			// increment position
			void inc_position()
			{
				position = position + 1;
			}

			void inc_speed()
			{
				speed = speed + 0.2f;
			}

		};
	}
}