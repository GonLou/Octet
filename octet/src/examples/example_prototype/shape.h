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
			int shape_type;
			boolean is_alive;
			int color;

			shape(int color, int line, int node, int time, int shape_type)
			{
				this->color = color;
				this->line = line;
				this->position = 0;
				this->node = node;
				this->speed = 0.5f;
				this->time = time;
				this->shape_type = shape_type;
				this->is_alive = true;
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

			void set_speed(float speed)
			{
				this->speed = speed;
			}

			void set_time(int time)
			{
				this->time = time;
			}

			void set_shape_type(int shape_type)
			{
				this->shape_type = shape_type;
			}

			void set_is_alive(int is_alive)
			{
				this->is_alive = is_alive;
			}

			void set_color(int color)
			{
				this->color = color;
			}

			// get
			int get_line()
			{
				return this->line;
			}

			int get_node()
			{
				return this->node;
			}

			int get_position()
			{
				return this->position;
			}

			float get_speed()
			{
				return this->speed;
			}

			int get_time()
			{
				return this->time;
			}

			int get_shape_type()
			{
				return this->shape_type;
			}

			boolean get_is_alive()
			{
				return this->is_alive;
			}

			int get_color()
			{
				return this->color;
			}

			// move the shapes
			void move(int node, ref<visual_scene> app_scene)
			{
				scene_node *move = app_scene->get_mesh_instance(node)->get_node();
				move->translate(vec3(0.0f, 0.0f, this->get_speed()));
				inc_position();
			}

			// increment position
			void inc_position()
			{
				this->position = this->position + 1;
			}

			void inc_speed()
			{
				this->speed = this->speed + 0.1f;
			}

			// destructor
			~shape(void)
			{
			}

		};
	}
}