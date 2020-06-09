#include "opengl_shader.hh"

#include "resource_handler.hh"
#include "parrot.hh"

#include <GL/glew.h>

#include <iostream>
#include <string>


namespace parrot{
	int Shader_Program::compile_shader(GLuint flags, std::string shadersource)
	{
		GLuint id = glCreateShader(flags);
		const char * src = shadersource.c_str();
		glShaderSource(id, 1, &src, NULL);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			char * message = (char *)alloca(sizeof(char) * length);
			glGetShaderInfoLog(id, length, &length, message);

			std::cout << "Failed to compile " << ((flags == GL_VERTEX_SHADER)? "vertex" : "fragment") << " shader" << std::endl;
			std::cout << message << std::endl;

			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	Shader_Source Shader_Program::load_shader_source(std::string shadersourcefile)
	{
		Shader_Source shadersource  = {};
		std::vector<std::string> source = Resource_Loader::load_file_in_string_vec(shadersourcefile);

		std::string buffer[SHADER_COUNT];
		int idx = -1;

		for(uint64 i = 0 ; i < source.size() ; i++)
		{
			if(source[i].find("#shader") != std::string::npos)
			{
				if(source[i].find("vertex") != std::string::npos)
					idx = 0;
				if(source[i].find("fragment") != std::string::npos)
					idx = 1;
			}
			else if(idx >= 0)
			{
				buffer[idx] += source[i] + "\n";
			}
		}

		shadersource.vertexsource = buffer[SHADER_VERTEX];
		shadersource.fragmentsource = buffer[SHADER_FRAGMENT];

		return shadersource;
	}

	void Shader_Program::load_shader_program(std::string shadersourcefile)
	{
		program = glCreateProgram();

		Shader_Source shadersource = load_shader_source(shadersourcefile);

		GLuint vs = compile_shader(GL_VERTEX_SHADER, shadersource.vertexsource);
		GLuint fs = compile_shader(GL_FRAGMENT_SHADER, shadersource.fragmentsource);

		if(vs == 0 || fs == 0){
			glDeleteProgram(program);
			program = 0;
		}

		glAttachShader(program, vs);
		glAttachShader(program, fs);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(fs);
		glDeleteShader(vs);
	}

	void Shader_Program::use_program()
	{
		glUseProgram(program);
	}

	void Shader_Program::unuse_program()
	{
		glUseProgram(0);
	}
}

