#ifndef PARROT_MESH_LOADER_HH
#define PARROT_MESH_LOADER_HH

#include "parrot.hh"
#include "mesh.hh"

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace parrot 
{
	class Mesh_Loader
	{
		public:
		static Mesh load_obj(std::string filename);
	};
}

#endif
