#include "index_buffer.hh"
#include "parrot.hh"

#include <GL/glew.h>


namespace parrot
{
	void Index_Buffer::bind() const  
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void Index_Buffer::unbind() const  
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Index_Buffer::Index_Buffer(void * dataptr, uint64 size, uint32 count, int type)
	{
		this->count = count;
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, dataptr, type);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	const uint32 Index_Buffer::get_count() const { return count ; }
}

