#ifndef NGX_INDEX_BUFFER

#include <GL/glew.h>

namespace ngx
{
	class Index_Buffer 
	{
		public:
		void bind() 
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		void unbind() 
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void create(void * dataptr, uint64 size, int type = GL_STATIC_DRAW)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, dataptr, type);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		private:

		GLuint id;

		// NOTE(nitesh) : We are not keeping track buffer in main memory 
		// instead we are sending the entire buffer in the GPU and using 
		// only the opengl handles to manipulate it (if ever) in any way
	};
}

#define NGX_INDEX_BUFFER 
#endif 
