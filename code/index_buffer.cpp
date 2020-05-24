#ifndef PARROT_INDEX_BUFFER

#include <GL/glew.h>

namespace parrot
{
	class Index_Buffer 
	{
		public:
		void bind() const  
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		void unbind() const  
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		Index_Buffer(void * dataptr, uint64 size, uint32 count, int type = GL_STATIC_DRAW)
		{
			this->count = count;
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, dataptr, type);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		const uint32 get_count() const { return count ; }

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
