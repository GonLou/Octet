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

			shape() //default constructor starts at middle line
			{
				line = 2;
				position = 0;
				node = 0;
			}

			shape(int line, int position, int node)
			{
				line = line;
				position = position;
				node = node;
			}

			// set
			void set_line(int line)
			{
				line = line;
			}

			void set_position(int pos)
			{
				position = pos;
			}

			void set_node(int node)
			{
				node = node;
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

			// move the shapes
			void move(int node, ref<visual_scene> app_scene)
			{
				scene_node *move = app_scene->get_mesh_instance(node)->get_node();
				move->translate(vec3(0, 0, 1));
				//inc_position();
			}

			// increment position
			void inc_position()
			{
				position = position + 1;
			}

		};
	}
}