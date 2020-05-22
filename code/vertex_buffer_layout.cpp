#ifndef NGX_VERTEX_BUFFER_LAYOUT

#include <GL/glew.h>

namespace ngx
{
	struct Vertex_Buffer_Layout_Element 
	{
		uint32 count;
		uint32 type;
		uint32 normalized;

		static uint64 get_type_size(uint32 type)
		{
			switch(type)
			{
				case GL_FLOAT: return sizeof(real32);
				case GL_UNSIGNED_INT: return sizeof(uint32);
				case GL_UNSIGNED_BYTE: return sizeof(uint8);
			}
			return 0;
		}
	};

	class Vertex_Buffer_Layout
	{
		public:

		void push(uint32 count, uint32 type)
		{
			Vertex_Buffer_Layout_Element element = {};
			element.count = count;
			element.type = type;
			element.normalized = GL_FALSE;

			stride += count * Vertex_Buffer_Layout_Element::get_type_size(type);

			elements.push_back(element);
		}

		inline uint32 get_stride(void) const {return stride;}

		inline std::vector<Vertex_Buffer_Layout_Element> const & get_elements(void) const { return elements;}

		private:
		uint32 stride = 0;
		std::vector<Vertex_Buffer_Layout_Element> elements;

	};
}

#define NGX_VERTEX_BUFFER_LAYOUT
#endif
