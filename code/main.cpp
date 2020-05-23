#include "ngx.cpp"
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
		ngx::Core::terminate_core();
}

struct Vertex
{
	ngx::real32 x, y, z;
	ngx::real32 r, g, b;
	ngx::real32 u, v;
};

int main()
{
	ngx::Core::init();

	ngx::Window main_window;
	main_window.create_widnow("main_window", 600, 430);
	ngx::InputHandler inputhandler; 

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
	
	ngx::uint32 indices[] = 
	{
		0, 1, 2,
		0, 2, 3
	};

	GLuint vao = 0;
	GLuint vbo = 0;

	ngx::Texture texture("res/wall.jpg");
	ngx::Vertex_Buffer vertexbuffer(vertices, sizeof(Vertex) *  4);
	ngx::Index_Buffer indexbuffer(indices, sizeof(ngx::uint32) * 6, 6);

	ngx::Shader_Program program ; 
	program.load_shader_program("shader/basic_shader.shader");

	ngx::Vertex_Array vertexarray;

	ngx::Vertex_Buffer_Layout bufferlayout;
	bufferlayout.push(3, GL_FLOAT); // vertices 
	bufferlayout.push(3, GL_FLOAT); // color
	bufferlayout.push(2, GL_FLOAT); // uv 
	
	vertexarray.add_vertex_buffer(vertexbuffer, bufferlayout);
	vertexarray.add_index_buffer(indexbuffer); 

	while(ngx::Core::is_running())
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
