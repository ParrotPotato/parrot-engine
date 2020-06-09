#ifndef PARROT_TEXTURE_LOADING

#include "parrot.hh"

#include <GL/glew.h>

#include <string>

namespace parrot
{
	class Texture
	{
		public: 
		Texture(std::string texturefilesource);

		void bind(int texture_unit);
		void unbind();

		private:
		GLuint texture_id_;
	};
}

#define PARROT_TEXTURE_LOADING
#endif

