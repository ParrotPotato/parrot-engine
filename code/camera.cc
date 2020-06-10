#include "camera.hh"

#include "parrot.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 


namespace parrot{

	glm::mat4 Camera::get_matrix(void)
	{
		// This is responsible for transforming objects 
		// from model space to world space this is more 
		// closely assocaited to the object itself
		glm::mat4 model = glm::mat4(1.0f);

		// This is responsible for transforming objects 
		// from workd space to camera / view space 
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(position, position + facing, up);

		// This is responsible for transforming objects
		// to a orthographic / prespective projects
		glm::mat4 projection = glm::perspective(glm::radians(90.0f),
				width / height, near, far);

		return projection * (view * model);
	}
}

