//////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Adapted by 
//				Goncalo Lourenco
//
//              Octet Shape Game 

using namespace std;

#include <vector>

#include "shape.h"

#include "engine.h"

namespace octet {
	/// Octet Shape Game

	class prototype : public app {
		// scene for the game
		ref<visual_scene> app_scene;
		dynarray<scene_node*> nodes;
		collada_builder loader;

		// track of objects from game
		//ref<shape> object_tracking[20]; 
		dynarray<ref<shape> > object_tracking;

		// variables for the game
		ref<engine> start;
		
		// helper for drawing text
		ref<text_overlay> overlay;

		// text mesh object for overlay.
		ref<mesh_text> text_left;
		ref<mesh_text> text_center;
		ref<mesh_text> text_right;

		int const TOTAL_OBJECTS = 40;

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

		// create the random shapes with random colors and random vertical positions
		void create_shape(int color, int shape_type, int object_time, int line)
		{
			mat4t modelToWorld;
			vec4 o_color;

			// define the object color
			switch (color) {
			case 1: // red color
				o_color = (vec4(1, 0, 0, 1));
				break;
			case 2: // green color
				o_color = (vec4(0, 1, 0, 1));
				break;
			case 3: //blue color
				o_color = (vec4(0, 0, 1, 1));
				break;
			}
			/*image *material_image = new image("assets/gonkas/material_texture.jpg");
			material *m_color = new material(material_image);*/
			material *m_color = new material(o_color);

			// define the vertical line alignment position
			switch (line) {
			case 1: // left
				modelToWorld.translate(-3.0f, 2.0f, -50.0f);
				break;
			case 2: // center
				modelToWorld.translate(0.0f, 2.0f, -50.0f);
				break;
			case 3: // right
				modelToWorld.translate(3.0f, 2.0f, -50.0f);
				break;
			}

			// define the object shape type
			switch (shape_type) {
			case 1: // cube
				add_box(modelToWorld, vec3(0.7f, 0.7f, 0.7f), m_color);
				break;
			case 2: // sphere
				add_sphere(modelToWorld, vec3(3.0f, 3.0f, 3.0f), m_color, 1.4f);
				break;
			case 3: // cylinder
				add_cylinder(modelToWorld, vec3(0.3f, 0.3f, 0.3f), m_color);
				break;
			}

			shape *object_shape = new shape(color, line, (int)nodes.size()-1, object_time, shape_type);
			object_tracking.push_back(object_shape);
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

			start->set_number_objects(TOTAL_OBJECTS);

			start->set_sound(true);

			mat4t modelToWorld;

			image *ground_image = new image("assets/gonkas/ground_texture.jpg");
			material *world_ground_material = new material(ground_image);

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
			int object_time;
			srand(time(NULL)); // initialize random seed

			for (int j = 0; j < start->get_number_objects(); j++) {
				color = (int) rand() % 3 + 1;
				shape_type = (int) rand() % 3 + 1;
				object_time = (int)rand() % (start->get_number_objects() * 50) + 1;
				line = (int) rand() % 3 + 1;
				create_shape(color, shape_type, object_time, line);
			}
			
			// change the active shape
			start->set_active_shape(object_tracking[0]->get_shape_type());

			/*for (unsigned i = 0; i < (object_tracking.size()-1); ++i)
			printf("id = %d || color = %d || line = %d || shape = %d\n", i, object_tracking[i]->get_color(), object_tracking[i]->get_line(), object_tracking[i]->get_shape_type());*/

			// text creation
			overlay = new text_overlay(); // create the overlay
			bitmap_font *font = overlay->get_default_font(); // get the default font.
			// create a box containing text (in pixels)
			aabb bb(vec3(100.0f, 100.0f, 0.0f), vec3(600, 150, 0));
			text_left = new mesh_text(font, "", &bb);
			aabb ab(vec3(150.0f, 100.0f, 0.0f), vec3(200, 150, 0));
			text_center = new mesh_text(font, "", &ab);
			aabb aa(vec3(500.0f, 100.0f, 0.0f), vec3(100, 150, 0));
			text_right = new mesh_text(font, "", &aa);
			// add the mesh to the overlay.
			overlay->add_mesh_text(text_left);
			overlay->add_mesh_text(text_center);
			overlay->add_mesh_text(text_right);

			// play the background music
			//PlaySound(TEXT("../../../assets/gonkas/music.wav"), NULL, SND_LOOP | SND_ASYNC);

		}

		void display_text(ref<engine> start, string mid_text, int vx, int vy) {
			// clear the text
			text_left->clear();
			text_center->clear();
			text_right->clear();
			// format the text
			text_left->format(
				"active shape: %s\nobjects collected:\n\t\tCube     -> %d\n\t\tSphere   -> %d\n\t\tCylinder -> %d\n",
				start->get_active_shape_text(), start->get_cubes(), start->get_spheres(), start->get_cylinders()
				);
			text_center->format("%s", mid_text);
			text_right->format("lives %d\n%s\n%d shapes\n%d points", 
				                start->get_lives(), start->get_sound_text(), start->get_number_objects(), start->get_points());
			// convert it to a mesh.
			text_left->update();
			text_center->update();
			text_right->update(); 
			overlay->render(vx, vy); // draw the text overlay
		}

		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {
			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);

			//printf("som %s\n",start->get_sound());

			if (start->get_start_game()) {
				start->inc_timer();

				{  	// >>> begin keyboard

					//ship controls
					scene_node *ship_controller = app_scene->get_mesh_instance(6)->get_node();
					if (start->get_ship_location() >= -12 && start->get_ship_location() <= 12) {
						if (app::is_key_down(key_left) || app::is_key_going_up(key_left)) {
							start->dec_ship_location();
							ship_controller->translate(vec3(0, -0.3f, 0));
							if (start->get_ship_location() <= -12)
							{
								ship_controller->translate(vec3(0, 0.3f, 0));
								start->inc_ship_location();
							}

						}
						if (app::is_key_down(key_right) || app::is_key_going_up(key_right)) {
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
					if (app::is_key_down('A')) {
						cam_node->rotate(5, vec3(0, 1, 0));
						start->set_camera_orientation(start->get_camera_orientation() + 1);
					}
					if (app::is_key_up('A')) {
						cam_node->rotate(-5 * start->get_camera_orientation(), vec3(0, 1, 0));
						start->set_camera_orientation(0);
					}
					if (app::is_key_down('D')) {
						cam_node->rotate(-5, vec3(0, 1, 0));
						start->set_camera_orientation(start->get_camera_orientation() + 1);
					}
					if (app::is_key_up('D')) {
						cam_node->rotate(5 * start->get_camera_orientation(), vec3(0, 1, 0));
						start->set_camera_orientation(0);
					}

					// toggle sound
					if (app::is_key_down('M')) {
						start->set_sound(true);
					}
					if (app::is_key_down('N')) {			
						PlaySound(NULL, 0, SND_ASYNC);
						start->set_sound(false);
					}

					// quit
					if (app::is_key_down('Q')) {
						exit(0);
					}

				} // end keyboard <<<

				/*for (unsigned i = 0; i < (object_tracking.size()-1); ++i) 
					printf("id = %d || color = %d || line = %d || shape = %d\n", i, object_tracking[i]->get_color(), object_tracking[i]->get_line(), object_tracking[i]->get_shape_type());*/

				for (unsigned i = 0; i < (object_tracking.size()); ++i) {
					if (object_tracking[i]->get_time() < start->get_timer()) { // if its time for the object to move
						object_tracking[i]->move(object_tracking[i]->get_node(), app_scene);
						if (i == object_tracking.size() || 
							i == (int)(object_tracking.size() / 2) || 
							i == (int)(object_tracking.size() / 3)) {
							if (   object_tracking[i]->get_time() < start->get_timer() + 2
								&& object_tracking[i]->get_time() > start->get_timer() - 2) {
								start->set_active_shape(object_tracking[i]->get_shape_type());
								if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/objective.wav"), NULL, SND_FILENAME | SND_ASYNC);
							}
						}
					}

					if (object_tracking[i]->get_position() > 140 && 
						object_tracking[i]->get_is_alive()) { // if is at the space ship zone verifies collision
						if (start->get_ship_location_transform() == object_tracking[i]->get_line()) { // verifies if collision occur
							if (start->get_active_shape() == object_tracking[i]->get_shape_type()) { // verifies if shape is the demanded
								start->process_shape(object_tracking[i]->get_shape_type()); // increment shape counter
								if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/collect.wav"), NULL, SND_FILENAME | SND_ASYNC);
								object_tracking[i]->fade(object_tracking[i]->get_node(), app_scene);
								object_tracking[i]->set_is_alive(false);
								start->set_number_objects(start->get_number_objects() - 1);
								start->set_points(((start->get_lives())*2 * 10)+start->get_points());
							}
							else {
								start->dec_lives(); // decrement live
								if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/collide.wav"), NULL, SND_FILENAME | SND_ASYNC);
								object_tracking[i]->set_is_alive(false);
								start->set_number_objects(start->get_number_objects() - 1);
							}
						}
						else { // if not collsion
							if (object_tracking[i]->get_position() > 160) {
								object_tracking[i]->set_is_alive(false);
								start->set_number_objects(start->get_number_objects() - 1);
							}
						}
					}
				}

				if ((object_tracking.size() * 50 + 150) < (start->get_timer())) {
					// display text
					//display_text(start, "Congratulations!\n You achieved\n 0 points", vx, vy);

					text_center->clear();
					text_center->format("Congratulations!\n You achieved\n 0 points");
					text_center->update();
					overlay->render(vx, vy); // draw the text overlay

					Sleep(5000);
					exit(0);
				}

				if (start->get_lives() < 0) {
					//display_text(start, "GAME OVER!\n You lost\nYou achieved\n 0 points", vx, vy);

					text_center->clear();
					text_center->format("GAME OVER!\n You lost\nYou achieved\n 0 pointss");
					text_center->update();
					overlay->render(vx, vy); // draw the text overlay

					if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);

					//getch(); // wait for a key get pressed
					Sleep(5000);
					exit(0);
				}

				// display text
				display_text(start, "", vx, vy);

			}
			else { // if game not started
				// text to start / quit game
				{
					if (app::is_key_down('S')) {
						start->set_game_start(true);
						PlaySound(NULL, 0, SND_ASYNC);
					}
					if (app::is_key_down('X')) {
						exit(0);
					}
				}

				// display text
				display_text(start, "Octet Shape Game\n[S]tart a Game\nE[x]it", vx, vy);	

			} // end of if starting game

			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);

		}

	};
}