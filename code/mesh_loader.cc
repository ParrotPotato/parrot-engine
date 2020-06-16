#include "mesh_loader.hh"

#include "parrot.hh"

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <unordered_map>

#include <sstream> 
#include <fstream> 
#include <iostream> 

namespace parrot
{

	// struct which is being used for 
	// vertex_normal_index index 
	struct vertex_normal_index
	{
		uint64 v;
		uint64 n;

		bool operator==(const vertex_normal_index & obj) const 
		{
			if(v == obj.v && n == obj.n)
				return true;
			return false;
		}
	};
	
	struct vertex_normal_index_functor
	{
		uint64 operator() (const vertex_normal_index & obj) const
		{
			// This is just something wacky that came to my mind
			return obj.v * obj.v + obj.n + obj.v / obj.n;
		}
	};

	// TODO(nitesh): Add functionality for loading obj file with multiple 
	// mesh (demarketed with g [meshname])

	Mesh Mesh_Loader::load_obj(std::string filename)
	{
//		std::cout << "[DEBUG] Parsing UV index of obj file not implemented yet" << std::endl;

		std::fstream meshfile(filename, std::ios::in);
		
		if(meshfile.fail())
		{
			std::cerr << "Unable to load file " << filename << std::endl;
			return {};
		}

		std::string line;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;

		std::unordered_map<vertex_normal_index, uint64, vertex_normal_index_functor> indicesbuffer;
		uint64 indexcount = 0;

		Mesh res = {};

		while(std::getline(meshfile, line, '\n'))
		{
//			std::cout << "line : " << line << std::endl;

			if(line[0] == 'v')
			{
				if(line[1] == 'n')
				{
					std::stringstream ss(line);
					glm::vec3 normal;
					
					// reading vn
					ss >> line;

					ss >> normal.x >> normal.y >> normal.z;

					normals.push_back(normal);

				}
				else if(line[1] == ' '){
					std::stringstream ss(line);
					glm::vec3 vertex;

					// reading v
					ss >> line;

					ss >> vertex.x >> vertex.y >> vertex.z;

					vertices.push_back(vertex);
				}
			
			}
			else if(line[0] == 'f')
			{
				// NOTE : obj files have face descriptions at the end 
				// thus we can assume that we are at the last segment 
				// of file and all teh data (vertices and normals) is
				// already read 
				//
				std::stringstream ss(line);

				// reading f
				ss >> line;
				
				while(ss >> line)
				{

//					std::cout << "Processing " << line << "[may cause errors]" << std::endl;
					
					std::stringstream iss(line);
					
					uint32 vals[3];

					for(int i=0 ; i < 3 ; ++i)
					{
						std::getline(iss, line, '/');
						if(line.size() == 0) continue;

//						std::cout << "internal line " << line << std::endl;
						vals[i] = std::stoi(line); 
//						std::cout << "value " << i << " : " << vals[i] << std::endl;
					}

					// Where magic happens 
					
					vertex_normal_index vni = {vals[0], vals[2]};

//					std::cout << "Searching for vni " << vni.v << " " << vni.n << std::endl;

					auto it = indicesbuffer.find(vni);

					if(it == indicesbuffer.end())
					{
						indicesbuffer[vni] = indexcount;
						
						// Add entry to mesh vertex normal and index buffer 

						// -1 because obj files stores indices starting with 
						// 1 instead of 0

						Vertex_Info vertexinfo  = 
						{
							vertices[vni.v - 1],
							normals[vni.n - 1]
						};

						res.vertices.push_back(vertexinfo);
						res.indices.push_back(indexcount);

						indexcount += 1;
					}
					else 
					{
						// we are setting the index for this vertex to the 
						// index of the already entered entry

						uint32 thatindex = it->second;

						// add that index to the index buffer

						res.indices.push_back(thatindex);

//						std::cout << "Searching fond that index " << thatindex << std::endl;
					}
				}
			}
		}
		return res;
		
	}
}
