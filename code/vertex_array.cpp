#ifndef NGX_VERTEX_ARRAY

#include "vertex_buffer.cpp"
#include "vertex_buffer_layout.cpp"

#include "index_buffer.cpp"

#include <GL/glew.h>

namespace ngx{

	class Vertex_Array
	{
		public:

		Vertex_Array(void)
		{
			glGenVertexArrays(1, &id);
		}

		void bind(void) const 
		{
			glBindVertexArray(id);
		}

		void unbind(void) const 
		{
			glBindVertexArray(0);
		}

		void add_vertex_buffer(const Vertex_Buffer & vb, const Vertex_Buffer_Layout & layout)
		{
			bind();
			vb.bind();

			const auto& elements = layout.get_elements();
			const uint32 stride = layout.get_stride();

			uint64 offset = 0;

			for(uint32 i = 0 ; i < elements.size() ; i++)
			{
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, stride, (void *) offset);
				offset += elements[i].count * Vertex_Buffer_Layout_Element::get_type_size(elements[i].type);
			}

			vb.unbind();
			unbind();
		}

		void draw()
		{
			glDrawElements(GL_TRIANGLES, indexsize, GL_UNSIGNED_INT, (void *) 0);	
		}

		void add_index_buffer(const Index_Buffer & ib)
		{
			bind();
			ib.bind();
			indexsize = ib.get_count();
			unbind();
		}

		private:
		GLuint id = 0;

		uint32 indexsize = 0;
	};
}

#define NGX_VERTEX_ARRAY
#endif 
