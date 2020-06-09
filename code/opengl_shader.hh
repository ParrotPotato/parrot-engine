#ifndef PARROT_OPENGL_SHADER

#include <GL/glew.h>

#include <string>


namespace parrot{

	enum Shader_Index 
	{
		SHADER_NONE = -1,
		SHADER_VERTEX = 0,
		SHADER_FRAGMENT = 1,

		SHADER_COUNT = 2
	};

	struct Shader_Source
	{
		std::string vertexsource;
		std::string fragmentsource;
	};

	class Shader_Program 
	{
		public:

		int compile_shader(GLuint flags, std::string shadersource);

		Shader_Source load_shader_source(std::string shadersourcefile);

		void load_shader_program(std::string shadersourcefile);

		void use_program();

		void unuse_program();

		private:

		GLuint program;
		GLuint vs;
		GLuint fs;
	};
}

#define PARROT_OPENGL_SHADER
#endif
