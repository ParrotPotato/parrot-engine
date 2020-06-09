#include "vertex_buffer.hh"
#include "parrot.hh"

#include <GL/glew.h>

namespace parrot
{
	void Vertex_Buffer::bind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void Vertex_Buffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Vertex_Buffer::Vertex_Buffer(void * dataptr, uint64 size, int type)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, dataptr, type);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

