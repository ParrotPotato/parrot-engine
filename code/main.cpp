#include "ngx.cpp"
#include "window.cpp"
#include "input.cpp"
#include "opengl_shader.cpp"

#include "vertex_buffer.cpp"
#include "index_buffer.cpp"

void keydown(int key)
{
	if(key == SDLK_ESCAPE)
		ngx::Core::terminate_core();
}


int main()
{
	ngx::Core::init();

	ngx::Window main_window;
	main_window.create_widnow("main_window", 600, 430);
	main_window.set_clear_color(74, 63, 63, 255);
	ngx::InputHandler inputhandler; 

	inputhandler.set_keydown_callback(keydown);
	
	// TODO(nitesh) : 
	// Just render a triangle with specific colors using indices
	//

	ngx::real32 vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	ngx::uint32 indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	ngx::real32 colors[] = {
		128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f,
		128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f,
		128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f,
		128.0f / 255.0f, 132.0f / 255.0f, 189.0f / 255.0f,
	};


	GLuint vao = 0;
	GLuint vbo = 0;

	ngx::Vertex_Buffer vertexbuffer;
	ngx::Vertex_Buffer vertexcolorbuffer;

	ngx::Index_Buffer indexbuffer;

	ngx::Shader_Program program ; 
	program.load_shader_program("shader/basic_shader.shader");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vertexcolorbuffer.create(colors, sizeof(ngx::real32) * 12);
	vertexbuffer.create(vertices, sizeof(ngx::real32) * 12);

	indexbuffer.create(indices, sizeof(ngx::uint32) * 6);
	indexbuffer.bind();

	vertexbuffer.bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

	vertexcolorbuffer.bind();
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

	glBindVertexArray(0);

	while(ngx::Core::is_running())
	{
		main_window.clear();
		glBindVertexArray(vao);
		program.use_program();
		//glDrawArrays(GL_TRIANGLES, 0, 9);
//		indexbuffer.bind();
		
		// in glDrawElements the last argument is the offset in the array 
		// where the indie buffer to be rendered is starting
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0);	

		program.unuse_program();
		glBindVertexArray(0);
		inputhandler.update();
		main_window.update();
	}

	return 0;
}
