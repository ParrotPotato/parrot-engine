#ifndef PARROT_VERTEX_ARRAY

#include "vertex_buffer.hh"
#include "vertex_buffer_layout.hh"
#include "index_buffer.hh"
#include "parrot.hh"

#include <GL/glew.h>

namespace parrot{

	class Vertex_Array
	{
		public:

		Vertex_Array(void);

		void bind(void) const ;

		void unbind(void) const ;
		void add_vertex_buffer(const Vertex_Buffer & vb, const Vertex_Buffer_Layout & layout);

		void draw();

		void add_index_buffer(const Index_Buffer & ib);

		private:
		GLuint id = 0;

		uint32 indexsize = 0;
	};
}

#define PARROT_VERTEX_ARRAY
#endif 

