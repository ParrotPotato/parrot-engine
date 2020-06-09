#ifndef PARROT_VERTEX_BUFFER

#include "parrot.hh"

#include <GL/glew.h>

namespace parrot
{
	class Vertex_Buffer
	{
		public:
		void bind() const ;
		void unbind() const;

		Vertex_Buffer(void * dataptr, uint64 size, int type = GL_STATIC_DRAW);

		private:

		GLuint id = 0;

		// NOTE(nitesh) : We are not keeping track buffer in main memory 
		// instead we are sending the entire buffer in the GPU and using 
		// only the opengl handles to manipulate it (if ever) in any way
	};
}

#define PARROT_VERTEX_BUFFER
#endif 

