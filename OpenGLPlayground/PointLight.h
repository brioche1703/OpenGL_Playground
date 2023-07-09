#pragma once

#include <glm/glm.hpp>

namespace Playground
{
	struct PointLight
	{
		glm::vec3 _position = glm::vec3(0.0f);
		glm::vec3 _ambient = glm::vec3(0.2f);
		glm::vec3 _diffuse = glm::vec3(0.5f);
		glm::vec3 _specular = glm::vec3(1.0f);
	};
}

