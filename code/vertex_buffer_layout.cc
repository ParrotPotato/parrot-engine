#include "vertex_buffer_layout.hh"
#include "parrot.hh"

#include <GL/glew.h>

namespace parrot
{

	uint64 Vertex_Buffer_Layout_Element::get_type_size(uint32 type)
	{
		switch(type)
		{
			case GL_FLOAT: return sizeof(real32);
			case GL_UNSIGNED_INT: return sizeof(uint32);
			case GL_UNSIGNED_BYTE: return sizeof(uint8);
		}
		return 0;
	}

	void Vertex_Buffer_Layout::push(uint32 count, uint32 type)
	{
		Vertex_Buffer_Layout_Element element = {};
		element.count = count;
		element.type = type;
		element.normalized = GL_FALSE;

		stride += count * Vertex_Buffer_Layout_Element::get_type_size(type);

		elements.push_back(element);
	}

	uint32 Vertex_Buffer_Layout::get_stride(void) const {return stride;}

	std::vector<Vertex_Buffer_Layout_Element> const & Vertex_Buffer_Layout::get_elements(void) const { return elements;}

}
