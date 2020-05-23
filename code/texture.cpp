#ifndef NGX_TEXTURE_LOADING

#include <string>
#include <fstream>

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ngx
{
	class Texture
	{
		public: 
		Texture(std::string texturefilesource)
		{
			glGenTextures(1, &texture_id_);

			glBindTexture(GL_TEXTURE_2D, texture_id_);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int32 width, height, nrchannel;
			unsigned char * buffer = stbi_load(texturefilesource.c_str(), &width, &height, &nrchannel, 0);

			if(buffer)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
				glGenerateMipmap(GL_TEXTURE_2D);
				stbi_image_free(buffer);
			}
			else 
			{
				std::cout << "Unable to load image " << texturefilesource << std::endl;
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void bind(int texture_unit)
		{
			glActiveTexture(texture_unit);
			glBindTexture(GL_TEXTURE_2D, texture_id_);
		}

		void unbind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		private:
		GLuint texture_id_;
	};
}

#define NGX_TEXTURE_LOADING
#endif
