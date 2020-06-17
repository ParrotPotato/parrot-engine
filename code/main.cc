#include "parrot.hh"
#include "window.hh"
#include "input.hh"
#include "camera.hh"

#include "texture.hh"

#include "opengl_shader.hh"
#include "mesh_loader.hh"

#include "vertex_array.hh"
#include "vertex_buffer.hh"
#include "index_buffer.hh"

#include <glm/gtx/rotate_vector.hpp>

// NOTE(nitesh): We are not able to access out local variables when 
// we are updating from this call back. This may cause some issues 
// down the road 

void keydown(int key)
{
	if(key == SDLK_ESCAPE)
		parrot::Core::terminate_core();
}

// INFO(nitesh): Handling input and VERTEX buffer 
// for specified object and type

struct Vertex
{
	parrot::real32 x, y, z;
	parrot::real32 r, g, b;
	parrot::real32 u, v;
};

int main()
{
	parrot::Core::init();

	parrot::Window main_window;
	main_window.create_widnow("main_window", 600, 430);
	parrot::InputHandler inputhandler; 

	inputhandler.set_keydown_callback(keydown);
	
	// TODO(nitesh) : 
	// Just render a triangle with specific colors using indices
	//

	Vertex vertices[] = {
		{-0.5f, -0.5f, 0.0f, 128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f, 0.0f, 0.0f},
		{0.5f, -0.5f, 0.0f, 128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f, 1.0f, 0.0f},
		{0.5f, 0.5f, 0.0f, 128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f, 1.0f, 1.0f},
		{-0.5f, 0.5f, 0.0f, 128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f, 0.0f, 1.0f}
	};
	
	parrot::uint32 indices[] = 
	{
		0, 1, 2,
		0, 2, 3
	};

	parrot::Texture texture("res/wall.jpg");
	parrot::Vertex_Buffer vertexbuffer(vertices, sizeof(Vertex) *  4);
	parrot::Index_Buffer indexbuffer(indices, sizeof(parrot::uint32) * 6, 6);

	parrot::Camera camera = {};

	camera.position = glm::vec3(0.0f, 0.0f, 1.0f);
	camera.facing = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	camera.width = main_window.get_width();
	camera.height = main_window.get_height();
	camera.near = 0.1f;
	camera.far = 1000.0f;

	parrot::Shader_Program program ; 
	program.load_shader_program("shader/basic_shader.shader");

	parrot::Vertex_Array vertexarray;

	parrot::Vertex_Buffer_Layout bufferlayout;
	bufferlayout.push(3, GL_FLOAT); // vertices 
	bufferlayout.push(3, GL_FLOAT); // color
	bufferlayout.push(2, GL_FLOAT); // uv 
	
	vertexarray.add_vertex_buffer(vertexbuffer, bufferlayout);
	vertexarray.add_index_buffer(indexbuffer); 

	// Trying to load cube mesh 
	parrot::Mesh cubemesh = parrot::Mesh_Loader::load_obj("mesh/cube.obj");

	parrot::real32 t = 0;

	parrot::real32 speed = 0.1f ;
	parrot::real32 rotation_speed = 0.8f;

	auto keydown_lambda = [&](int key)
	{

		if(key == SDLK_ESCAPE)
		{
			parrot::Core::terminate_core();
		}
		else if(key == SDLK_a)
		{
			camera.position = camera.position - speed * glm::normalize(glm::cross(camera.facing, camera.up));
		}
		else if(key == SDLK_d)
		{
			camera.position = camera.position + speed * glm::normalize(glm::cross(camera.facing, camera.up));
		}
		else if(key == SDLK_w)
		{
			camera.position = camera.position + speed * camera.facing;
		}
		else if(key == SDLK_s)
		{
			camera.position = camera.position - speed * camera.facing;
		}

		else if(key == SDLK_q)
		{
			camera.facing = glm::rotate(camera.facing, glm::radians(rotation_speed), glm::vec3(camera.up));
		}
		else if(key == SDLK_e)
		{
			camera.facing = glm::rotate(camera.facing, -glm::radians(rotation_speed), glm::vec3(camera.up));
		}

	};

	inputhandler.set_keydown_callback(keydown_lambda);
	inputhandler.set_keypress_callback(keydown_lambda);

	while(parrot::Core::is_running())
	{	

	//	camera.position = glm::vec3(0.0f, 0.0f, 3.0f) + glm::vec3(0.0f, 0.0f, std::sin(t) * 2.0f);
	//	camera.facing = glm::rotate(camera.facing, glm::radians(t), glm::vec3(0.0f, 1.0f, 0.0f));
		
		main_window.clear();

		texture.bind(GL_TEXTURE0);
		vertexarray.bind();
		program.use_program();
		program.set_uniform("transformation", camera.get_matrix());
		
		vertexarray.draw();

		program.unuse_program();
		vertexarray.unbind();
		
		inputhandler.update();
		main_window.update();

		t = 0.8f;
	}

	return 0;
}
