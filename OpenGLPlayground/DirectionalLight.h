#pragma once

#include <glm/glm.hpp>

namespace Playground
{
	struct DirectionalLight
	{
		glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		glm::vec3 _ambient = glm::vec3(0.2f);
		glm::vec3 _diffuse = glm::vec3(0.5f);
		glm::vec3 _specular = glm::vec3(1.0f);
	};
}

