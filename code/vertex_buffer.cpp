#ifndef NGX_VERTEX_BUFFER

#include <GL/glew.h>

namespace ngx
{
	class Vertex_Buffer
	{
		public:
		void bind() const 
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Vertex_Buffer(void * dataptr, uint64 size, int type = GL_STATIC_DRAW)
		{
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, dataptr, type);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		private:

		GLuint id = 0;

		// NOTE(nitesh) : We are not keeping track buffer in main memory 
		// instead we are sending the entire buffer in the GPU and using 
		// only the opengl handles to manipulate it (if ever) in any way
	};
}

#define NGX_VERTEX_BUFFER
#endif 
