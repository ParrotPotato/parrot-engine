#ifndef PARROT_CAMERA_HH
#define PARROT_CAMERA_HH

#include "parrot.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace parrot{
	
	struct Camera{

		glm::mat4 get_matrix(void);
		Camera(glm::vec3 position, real32 widht, real32 height);
		Camera(){} // Do nothing

		glm::vec3 position;
		glm::vec3 facing;
		glm::vec3 up;

		real32 width;
		real32 height;

		real32 near;
		real32 far;
	};
}

#endif
