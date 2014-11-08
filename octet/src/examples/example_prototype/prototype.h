//////////////////////////////////////////////////////////////////////////////
//
//				Goncalo Lourenco
//
//              Octet Shape Game 
//
//				the objective is to collect shapes indicated avoiding the remaining shapes

using namespace std;

#include <vector>

#include "shape.h"

#include "engine.h"

#include "greeble.h"

namespace octet {
	/// Octet Shape Game

	class prototype : public app {
		// scene for the game
		ref<visual_scene> app_scene;
		dynarray<scene_node*> nodes;
		collada_builder loader;

		// track of objects from game
		dynarray<ref<shape> > object_tracking;

		dynarray<ref<greeble> > city;

		// variables for the game
		ref<engine> start;
		
		// helper for drawing text
		ref<text_overlay> overlay;

		// text mesh object for overlay.
		ref<mesh_text> text_left;
		ref<mesh_text> text_center;
		ref<mesh_text> text_right;

		//construct a box
		//
		void add_box(mat4t_in modelToWorld, vec3_in size, material *mat) {
			mesh_box *box = new mesh_box(size);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, box, mat));
		}

		//construct a sphere
		//
		void add_sphere(mat4t_in modelToWorld, vec3_in size, material *mat, float radius) {
			mesh_sphere *sphere = new mesh_sphere(size, radius, 2);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, sphere, mat));
		}

		//construct a cylinder
		//
		void add_cylinder(mat4t_in modelToWorld, vec3_in size, material *mat) {
			mesh_cylinder *cylinder = new mesh_cylinder(size, 1, 24);
			scene_node *node = new scene_node(modelToWorld, atom_);
			nodes.push_back(node);

			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, cylinder, mat));
		}

		//import a collada object
		//
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

				app_scene->add_child(node);
				app_scene->add_mesh_instance(new mesh_instance(node, spaceship, mat));
			}

		}

		// create the random shapes with random colors and random vertical positions
		//
		void create_shape(int color, int shape_type, int object_time, int line) {
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

		// generates the boxes for the greeble
		//
		void greeble_generator(float greeble_w, float greeble_h, float greeble_d, int greeble_seed, int angle, int x_start, int z_pos) {
			mat4t modelToWorld;
			int scale = 2;
			image *material_image = new image("assets/gonkas/ground_texture.jpg");
			material *greeble_mat = new material(material_image);

			modelToWorld.translate(x_start, 5.0f - (5-greeble_h), -25.0f + z_pos);

			switch (greeble_seed) {
				case 1: 
				case 2:
				default:
					add_box(modelToWorld, vec3(greeble_w / scale, greeble_h / scale, greeble_d / scale), greeble_mat);
			}

			modelToWorld.rotateY(angle);

		}

		// creates a city blocks 
		//
		void greeble_call(int z_pos) {
			mat4t modelToWorld;

			int min = 1;
			int max = 5;
			int greeble_total = 5;
			int angle[] = {0, 45, 90, 125, 180, 225, 270, 315};
			float greeble_seed = rand() % 4 + 1;
			float greeble_w = (rand() % max + min);
			float greeble_h = (rand() % max + min);
			int greeble_d = 1;

			int x_bound_left = -12;
			int x_bound_right = 12;
			
			if (greeble_h < greeble_w) {
				greeble_d = greeble_h;
				greeble_h = greeble_w;
			}
			else greeble_d = greeble_w;

			// generates both sides of city blocks
			greeble *city_gen = new greeble((int)nodes.size(), 0, z_pos);
			for (unsigned g = 0; g < greeble_total; g++) {
				greeble_generator(greeble_w, greeble_h, greeble_d, greeble_seed, angle[(int)rand() % 7], x_bound_left, z_pos);
				greeble_generator(greeble_w, greeble_h, greeble_d, greeble_seed, angle[(int)rand() % 7], x_bound_right, z_pos);

				x_bound_left = x_bound_left + (greeble_w*(1 - 2));
				x_bound_right = x_bound_right + greeble_w;
				greeble_seed = (int)rand() % 4 + 1;
				greeble_w = (rand() % max + min);
				greeble_h = (rand() % max + min);
				greeble_d = 1;

				greeble_h < greeble_w ? greeble_d = greeble_h : greeble_d = greeble_w;
			}
			city_gen->set_node_end((int)nodes.size() - 1);
			city.push_back(city_gen);

		}

		// generates the text in 3 different places
		//
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
			// draw the text overlay
			overlay->render(vx, vy); 
		}

	public:
		/// this is called when we construct the class before everything is initialised.
		prototype(int argc, char **argv) : app(argc, argv) {
		}

		/// this is called once OpenGL is initialized
		void app_init() {
			// total objects of the game
			int const TOTAL_OBJECTS = 40;

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
			printf("sky deployed\n");

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
			modelToWorld.translate(-12.35f, 1.43f, 0);
			add_box(modelToWorld, vec3(10.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.translate(38.60f, -0.05f, 0);
			add_box(modelToWorld, vec3(10.0f, 0.5f, 50.0f), world_ground_material);
			modelToWorld.translate(-5.0f, 0.0f, 0.0f);
			printf("ground deployed\n");

			// create 2 placards
			modelToWorld.translate(-14.30f, 5.0f, 15.0f);
			image *game_over_image = new image("assets/gonkas/game_over.jpg");
			material *m_img01 = new material(game_over_image);
			add_box(modelToWorld, vec3(10.7f, 3.7f, 0.0f), m_img01);
			printf("placard #1 deployed\n");
			image *end_game_image = new image("assets/gonkas/end_game.jpg");
			material *m_img02 = new material(end_game_image);
			add_box(modelToWorld, vec3(10.7f, 3.7f, 0.0f), m_img02);
			printf("placard #2 deployed\n");

			// add spaceship
			image *spaceship_image = new image("assets/gonkas/spaceship_texture.jpg");
			material *spaceship_material = new material(spaceship_image);
			modelToWorld.translate(14.30f, -5.0f, -15.0f);
			modelToWorld.scale(0.30f, 0.30f, 0.30f);
			//modelToWorld.rotateY(90);
			modelToWorld.rotateX(90);
			modelToWorld.rotateZ(180);
			//modelToWorld.translate(-20.0f, -14.0f, 1.8f);
			modelToWorld.translate(48.0f, -80.0f, 0.0f);		
			add_collada(modelToWorld, vec3(1.0f, 1.0f, 1.0f), spaceship_material, "assets/gonkas/ship.dae");
			start->set_node_spaceship((int)nodes.size() - 1);
			printf("ship deployed\n");

			// random objects creation
			int color;
			int shape_type;
			int line;
			int object_time;
			srand(time(NULL)); // initialize random seed

			for (int j = 0; j < start->get_number_objects(); j++) {
				color = (int)rand() % 3 + 1;
				shape_type = (int)rand() % 3 + 1;
				object_time = (int)rand() % (start->get_number_objects() * 50) + 1;
				line = (int)rand() % 3 + 1;
				create_shape(color, shape_type, object_time, line);
			}

			// change the active shape
			start->set_active_shape(object_tracking[0]->get_shape_type());

			// for control purposes only
			for (unsigned i = 0; i < (object_tracking.size() - 1); ++i)
				printf("id = %d || color = %d || line = %d || shape = %d\n", i, object_tracking[i]->get_color(), object_tracking[i]->get_line(), object_tracking[i]->get_shape_type());

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

			// push the placards to a place not visible
			scene_node *placard_end_game = app_scene->get_mesh_instance(start->get_node_spaceship() - 1)->get_node();
			placard_end_game->translate(vec3(0, 0, start->get_end_game_counter()*(1 - 2)));
			scene_node *placard_game_over = app_scene->get_mesh_instance(start->get_node_spaceship() - 2)->get_node();
			placard_game_over->translate(vec3(0, 0, start->get_end_game_counter()*(1 - 2)));

			// add the city blocks
			for (int i = -100; i < 0; i = i + 10) {
				greeble_call(i);
				printf("building #%d created\n", (i/10)*(1-2));
			}

			// play the background music
			PlaySound(TEXT("../../../assets/gonkas/music.wav"), NULL, SND_LOOP | SND_ASYNC);

		}

		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {
			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);
			const float displacement = 0.9f;

			if (start->get_game_start()) {
				start->inc_timer();

				// animates the city blocks
				for (unsigned i = 0; i < (city.size()); ++i) {
					city[i]->move(app_scene);					
					if (city[i]->get_position() > 250) city[i]->reset(app_scene);
				}

				{  	// begin keyboard

					//ship controls
					scene_node *ship_controller = app_scene->get_mesh_instance(start->get_node_spaceship())->get_node();
					if (start->get_ship_location() >= -12 && start->get_ship_location() <= 12) {
						// left move
						if (app::is_key_down(key_left) || app::is_key_going_up(key_left)) {
							start->dec_ship_location();
							ship_controller->translate(vec3(displacement, 0, 0));
							if (start->get_ship_location() <= -12)
							{
								ship_controller->translate(vec3(displacement*(1 - 2), 0, 0));
								start->inc_ship_location();
							}

						}
						// right move
						if (app::is_key_down(key_right) || app::is_key_going_up(key_right)) {
							start->inc_ship_location();
							ship_controller->translate(vec3(displacement*(1 - 2), 0, 0));
							if (start->get_ship_location() >= 12)
							{
								ship_controller->translate(vec3(displacement, 0, 0));
								start->dec_ship_location();
							}
						}
					}

					//camera controls
					scene_node *cam_node = app_scene->get_camera_instance(0)->get_node();
					// left move
					if (app::is_key_down('A')) {
						cam_node->rotate(5, vec3(0, 1, 0));
						start->set_camera_orientation(start->get_camera_orientation() + 1);
					}
					// key up reset to original camera position
					if (app::is_key_up('A')) {
						cam_node->rotate(-5 * start->get_camera_orientation(), vec3(0, 1, 0));
						start->set_camera_orientation(0);
					}
					// right move
					if (app::is_key_down('D')) {
						cam_node->rotate(-5, vec3(0, 1, 0));
						start->set_camera_orientation(start->get_camera_orientation() + 1);
					}
					// key up reset to original camera position
					if (app::is_key_up('D')) {
						cam_node->rotate(5 * start->get_camera_orientation(), vec3(0, 1, 0));
						start->set_camera_orientation(0);
					}

					// toggle sound on
					if (app::is_key_down('M')) {
						start->set_sound(true);
					}
					// toggle sound off
					if (app::is_key_down('N')) {
						PlaySound(NULL, 0, SND_ASYNC);
						start->set_sound(false);
					}

					// quick quit
					if (app::is_key_down('Q')) {
						exit(0);
					}

				} // end keyboard
				
				// animates the active shapes
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

					// collision detection
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
								start->dec_lives(); // decrement one live
								if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/collide.wav"), NULL, SND_FILENAME | SND_ASYNC);
								object_tracking[i]->set_is_alive(false);
								start->set_number_objects(start->get_number_objects() - 1);
							}
						}
						else { // if not collision the object just goes out of screen
							if (object_tracking[i]->get_position() > 160) {
								object_tracking[i]->set_is_alive(false);
								start->set_number_objects(start->get_number_objects() - 1);
							}
						}
					}
				}

				// the game ended with sucess
				if ((object_tracking.size() * 50 + 150) < (start->get_timer())) {
					// play the background music
					if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/music.wav"), NULL, SND_LOOP | SND_ASYNC);

					start->set_game_start(false);
				}

				// game over
				if (start->get_lives() < 0) {
					// play the explosion sound
					if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
					start->set_game_start(false);
				}

				// display text
				display_text(start, "", vx, vy);

			}
			else { // if game not started

				if ((object_tracking.size() * 50 + 150) < (start->get_timer())) { // the game ended with sucess
					scene_node *placard_end_game = app_scene->get_mesh_instance(start->get_node_spaceship() - 1)->get_node();
					placard_end_game->translate(vec3(0, 0, 1));
					start->set_end_game_counter(start->get_end_game_counter() - 1);

					if (start->get_end_game_counter() <= 0) {
						Sleep(5000);
						exit(0);
					}
				}
				else if (start->get_lives() < 0) { // game over
					scene_node *placard_game_over = app_scene->get_mesh_instance(start->get_node_spaceship() - 2)->get_node();
					placard_game_over->translate(vec3(0, 0, 1));
					start->set_end_game_counter(start->get_end_game_counter() - 1);

					if (start->get_end_game_counter() <= 0) {
						if (start->get_sound()) PlaySound(TEXT("../../../assets/gonkas/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(5000);
						exit(0);
					}
				}
				else { 	
					{ // keys to start / quit game
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
				}

			} // end of if starting game

			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);

		}

	};
}