#ifndef PARROT_OPENGL_SHADER

#include "parrot.hh"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>


namespace parrot{

	enum Shader_Index 
	{
		SHADER_NONE = -1,
		SHADER_VERTEX = 0,
		SHADER_FRAGMENT = 1,

		SHADER_COUNT = 2
	};

	struct Uniform_Info
	{
		std::string name;
		GLint location;
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

		int set_uniform(std::string name, glm::mat4 matval);
		int set_uniform(std::string name, real32 realval);

		private:

		Uniform_Info add_uniform(std::string name);

		GLuint program;
		GLuint vs;
		GLuint fs;

		std::vector<Uniform_Info> uniforms;
		
	};
}

#define PARROT_OPENGL_SHADER
#endif
