#include "parrot.cpp"
#include "window.cpp"
#include "input.cpp"

#include "texture.cpp"

#include "opengl_shader.cpp"

#include "vertex_array.cpp"
#include "vertex_buffer.cpp"
#include "index_buffer.cpp"

void keydown(int key)
{
	if(key == SDLK_ESCAPE)
		parrot::Core::terminate_core();
}

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

	parrot::Shader_Program program ; 
	program.load_shader_program("shader/basic_shader.shader");

	parrot::Vertex_Array vertexarray;

	parrot::Vertex_Buffer_Layout bufferlayout;
	bufferlayout.push(3, GL_FLOAT); // vertices 
	bufferlayout.push(3, GL_FLOAT); // color
	bufferlayout.push(2, GL_FLOAT); // uv 
	
	vertexarray.add_vertex_buffer(vertexbuffer, bufferlayout);
	vertexarray.add_index_buffer(indexbuffer); 

	while(parrot::Core::is_running())
	{
		main_window.clear();

		texture.bind(GL_TEXTURE0);
		vertexarray.bind();
		program.use_program();
		
		vertexarray.draw();

		program.unuse_program();
		vertexarray.unbind();
		
		inputhandler.update();
		main_window.update();
	}

	return 0;
}
