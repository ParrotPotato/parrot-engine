#ifndef PARROT_INDEX_BUFFER

#include "parrot.hh"

#include <GL/glew.h>

namespace parrot
{
	class Index_Buffer 
	{
		public:
		void bind() const;
		void unbind() const;

		Index_Buffer(void * dataptr, uint64 size, uint32 count, int type = GL_STATIC_DRAW);

		const uint32 get_count() const;

		private:

		GLuint id = 0;
		uint32 count = 0;

		// NOTE(nitesh) : We are not keeping track buffer in main memory 
		// instead we are sending the entire buffer in the GPU and using 
		// only the opengl handles to manipulate it (if ever) in any way
	};
}

#define PARROT_INDEX_BUFFER 
#endif 
