//////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Adapted by 
//				Goncalo Lourenco
//
// Octet Game Shape

#include "shape.h"

#include "engine.h"

//#include "play_sound.h"

namespace octet {
	/// Octet Shape Game

	class prototype : public app {
		// scene for the game
		ref<visual_scene> app_scene;
		dynarray<scene_node*> nodes;
		collada_builder loader;

		// track of objects from game
		ref<shape> object_tracking[40]; 

		// variables for the game
		ref<engine> start;

		// helper for drawing text
		ref<text_overlay> overlay;

		// text mesh object for overlay.
		ref<mesh_text> text_left;
		ref<mesh_text> text_right;

		//construct a box
		void add_box(mat4t_in modelToWorld, vec3_in size, material *mat) {
			mesh_box *box = new mesh_box(size);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, box, mat));
		}

		//construct a sphere
		void add_sphere(mat4t_in modelToWorld, vec3_in size, material *mat, float radius) {
			mesh_sphere *sphere = new mesh_sphere(size, radius, 2);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, sphere, mat));
		}

		//construct a cylinder
		void add_cylinder(mat4t_in modelToWorld, vec3_in size, material *mat) {
			mesh_cylinder *cylinder = new mesh_cylinder(size, 1, 24);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, cylinder, mat));
		}

		//import a collada object
		void add_collada(mat4t_in modelToWorld, vec3_in size, material *mat, string file_name) {

			resource_dict dict;
			if (!loader.load_xml(file_name)) {
				return;
			}
			loader.get_resources(dict);

			dynarray<resource*> meshes;
			dict.find_all(meshes, atom_mesh);

			if (meshes.size()) {
				mesh *spaceship = meshes[0]->get_mesh();

				scene_node *node = new scene_node(modelToWorld, atom_);
				nodes.push_back(node);

				//node->rotate(90, vec3(1, 1, 0));
				app_scene->add_child(node);
				app_scene->add_mesh_instance(new mesh_instance(node, spaceship, mat));
			}

		}

		void shake() {

			float **p2DArray;
			const int HEIGHT = 50;
			const int WIDTH = 3;

			p2DArray = new float*[HEIGHT];
			for (int i = 0; i < HEIGHT; ++i)
				p2DArray[i] = new float[WIDTH];

			// assing the values
			for (int i = 0; i < HEIGHT; i++)
			{
				p2DArray[i][0] = (rand() % 10 + 1) / 8;
				p2DArray[i][1] = (rand() % 10 + 1) / 8;
				p2DArray[i][2] = (rand() % 10 + 1) / 8;
			}

			// pass the values
			for (int i = 0; i < HEIGHT; i++)
			{
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(p2DArray[i][0], p2DArray[i][1], p2DArray[i][2]));
				Sleep(10);
			}
			for (int i = 0; i < HEIGHT; i++)
			{
				app_scene->get_camera_instance(0)->get_node()->translate(vec3(p2DArray[i][0] * (1 - 2), p2DArray[i][1] * (1 - 2), p2DArray[i][2] * (1 - 2)));
				Sleep(10);
			}

			// deallocate memory to prevent memory leak
			for (int i = 0; i < HEIGHT; ++i)
				delete[] p2DArray[i];
			delete[] p2DArray;

		}
		
		//void create_shape(int color, int shape_type, int line)
		void create_shape(int index, int color, int shape_type, int line)
		{
			mat4t modelToWorld;
			//modelToWorld.translate(-14.30f, -1.0f, 25.0f);
			//param_shader *shader = new param_shader("shaders/default.vs", "shaders/gonkas.fs");

			// define the object color
			vec4 o_color;
			switch (color)
			{
			case 1: // red color
				o_color = (vec4(1, 0, 0, 1));
				break;
			case 2: // green color
				o_color = (vec4(0, 1, 0, 1));
				break;
			case 3: //blue color
			default:
				o_color = (vec4(0, 0, 1, 1));
				break;
			}
			material *m_color = new material(o_color);

			// define the vertical line alignment position
			int a_line[3] = { -3, 0, 3 };
			int a_line_negative[3] = { 3, 0, -3 };
			int timer;
			modelToWorld.translate(a_line[line-1], 2.0, -30.0);

			// define the object shape type
			switch (shape_type)
			{
			case 1: // cube
				add_box(modelToWorld, vec3(0.7f, 0.7f, 0.7f), m_color);
				break;
			case 2: // sphere
				add_sphere(modelToWorld, vec3(3.0f, 3.0f, 3.0f), m_color, 1.4f);
				break;
			case 3: // cylinder
			default:
				add_cylinder(modelToWorld, vec3(0.3f, 0.3f, 0.3f), m_color);
				break;
			}

			// gain back the position
			modelToWorld.translate(a_line_negative[line-1], -2.0f, 30.0f);
			timer = rand() % (start->get_number_objects() * 50) + 1;
			object_tracking[index] = new shape(line, 0, (int)nodes.size(), timer);
		}


	public:
		/// this is called when we construct the class before everything is initialised.
		prototype(int argc, char **argv) : app(argc, argv) {
		}

		/// this is called once OpenGL is initialized
		void app_init() {
			app_scene = new visual_scene();
			app_scene->create_default_camera_and_lights();
			app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 5, 0));

			// initialize all engine variables
			start = new engine();

			start->set_number_objects(40);

			object_tracking[start->get_number_objects()];

			// load sounds
			/*play_sound background_music("../../../assets/gonkas/music.wav");
			play_sound colect("../../../assets/gonkas/colect.wav");
			play_sound collide("../../../assets/gonkas/collide.wav");
			play_sound explosion("../../../assets/gonkas/explosion.wav");
			play_sound objective("../../../assets/gonkas/objective.wav");*/

			mat4t modelToWorld;

			image *img01 = new image("assets/gonkas/ground_texture.jpg");
			material *world_ground_material = new material(img01);

			// create sky environment
			material *blue_sky = new material(vec4(0.5f, 0.5f, 1.0f, 1));
			modelToWorld.translate(0.0f, 0.0f, 5.0f);
			add_sphere(modelToWorld, vec3(1.0f, 1.0f, 1.0f), blue_sky, 39.0f);
			modelToWorld.translate(0.0f, 0.0f, -5.0f);

			// add the ground world (as a static object)
			add_box(modelToWorld, vec3(6.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.translate(7.0f, 1.5f, 0.0f);
			modelToWorld.rotateZ(30);
			add_box(modelToWorld, vec3(3.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.translate(-12.0f, 7.0f, 0.0f);
			modelToWorld.rotateZ(-60);
			add_box(modelToWorld, vec3(3.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.rotateZ(60);
			modelToWorld.rotateZ(-30);
			modelToWorld.translate(-7.35f, 1.43f, 0);
			add_box(modelToWorld, vec3(5.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.translate(28.60f, -0.05f, 0);
			add_box(modelToWorld, vec3(5.0f, 0.5f, 50.0f), world_ground_material);

			// add spaceship
			material *spaceship_material = new material(new image("assets/gonkas/spaceship_texture.jpg"), NULL); 
			//material *spaceship_material = new material(vec4(0.9f, 0.8f, 0.7f, 1));
			modelToWorld.rotateY(90);
			modelToWorld.rotateX(90);
			modelToWorld.translate(-20.0f, -14.0f, 1.8f);
			add_collada(modelToWorld, vec3(1.0f, 1.0f, 1.0f), spaceship_material, "assets/gonkas/spaceship.dae");

			// random objects creation
			int color;
			int shape_type;
			int line;
			srand(time(NULL)); // initialize random seed

			for (unsigned i = 0; i < start->get_number_objects(); i++)
			{
				color = rand() % 3 + 1;
				shape_type = rand() % 3 + 1;
				line = rand() % 3 + 1;
				create_shape(i, color, shape_type, line);
			}

			// text creation
			overlay = new text_overlay(); // create the overlay
			bitmap_font *font = overlay->get_default_font(); // get the default font.
			// create a box containing text (in pixels)
			aabb bb(vec3(100.0f, 100.0f, 0.0f), vec3(600, 150, 0));
			text_left = new mesh_text(font, "", &bb);
			aabb aa(vec3(500.0f, 100.0f, 0.0f), vec3(100, 150, 0));
			text_right = new mesh_text(font, "", &aa);
			// add the mesh to the overlay.
			overlay->add_mesh_text(text_left);
			overlay->add_mesh_text(text_right);

		}

		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {
			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);

			start->inc_timer();

			{  	// >>> begin keyboard

				//ship controls
				scene_node *ship_controller = app_scene->get_mesh_instance(6)->get_node();
				if (start->get_ship_location() >= -12 && start->get_ship_location() <= 12)
				{
					if (app::is_key_down(key_left)) {
						start->dec_ship_location();
						ship_controller->translate(vec3(0, -0.3f, 0));
						if (start->get_ship_location() <= -12)
						{
							ship_controller->translate(vec3(0, 0.3f, 0));
							start->inc_ship_location();
						}
					}
					if (app::is_key_down(key_right )) {
						start->inc_ship_location();
						ship_controller->translate(vec3(0, 0.3f, 0));
						if (start->get_ship_location() >= 12)
						{
							ship_controller->translate(vec3(0, -0.3f, 0));
							start->dec_ship_location();
						}
					}
				}

				//camera controls
				scene_node *cam_node = app_scene->get_camera_instance(0)->get_node();
				if (app::is_key_down('W')) {
					//shake();
					//cam_node->translate(vec3(0, 0, -1));
				}
				/*if (app::is_key_down('S')) {
					cam_node->translate(vec3(0, 0, 1));
				}*/
				if (app::is_key_down('A')) {
					cam_node->rotate(5, vec3(0, 1, 0));
				}
				if (app::is_key_down('D')) {
					cam_node->rotate(-5, vec3(0, 1, 0));
				}

				// toggle sound
				if (app::is_key_down('M')) {
					PlaySound(TEXT("../../../assets/gonkas/music.wav"), NULL, SND_LOOP | SND_ASYNC);
					start->set_sound_on();
				}
				if (app::is_key_down('N')) {			
					PlaySound(NULL, NULL, 0);
					start->set_sound_off();
				}

				// quit
				if (app::is_key_down('Q')) {
					exit(0);
				}

			} // end keyboard <<<

			for (unsigned i = 0; i < (start->get_number_objects()-1); ++i) {
				if (object_tracking[i]->get_time() < start->get_timer())
					object_tracking[i]->move(object_tracking[i]->get_node(), app_scene);
			}
	
			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);

			// display text
			text_left->clear();
			text_right->clear();
			text_left->format(
				"active shape: %s\nobjects collected:\n\t\tCube     -> %d\n\t\tSphere   -> %d\n\t\tCylinder -> %d\n",
				start->get_active_shape_text(), start->get_cubes(), start->get_spheres(), start->get_cylinders()
				);
			text_right->format("lives %d\n%s\n%d", start->get_lives(), start->get_sound(), start->get_timer());
			text_left->update();
			text_right->update(); // convert it to a mesh.
			overlay->render(vx, vy); // draw the text overlay
		}
	};

}