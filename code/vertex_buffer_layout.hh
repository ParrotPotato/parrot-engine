#ifndef PARROT_VERTEX_BUFFER_LAYOUT

#include "parrot.hh"

#include <GL/glew.h>

#include <vector>

namespace parrot
{
	struct Vertex_Buffer_Layout_Element 
	{
		uint32 count;
		uint32 type;
		uint32 normalized;

		static uint64 get_type_size(uint32 type);
	};

	class Vertex_Buffer_Layout
	{
		public:

		void push(uint32 count, uint32 type);

		uint32 get_stride(void) const;
		std::vector<Vertex_Buffer_Layout_Element> const & get_elements(void) const;

		private:
		uint32 stride = 0;
		std::vector<Vertex_Buffer_Layout_Element> elements;

	};
}

#define PARROT_VERTEX_BUFFER_LAYOUT
#endif

