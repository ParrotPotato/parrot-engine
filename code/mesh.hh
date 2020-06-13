#ifndef PARROT_MESH_HH
#define PARROT_MESH_HH

#include "parrot.hh"

#include <glm/glm.hpp> 

#include <vector>


namespace parrot
{
	struct Vertex_Info
	{
		glm::vec3 position;
		glm::vec3 normal;
	};

	struct Mesh 
	{
		std::vector<Vertex_Info> vertices;
		std::vector<uint32> indices;

		glm::mat4 model_matrix;
	};
}

#endif
