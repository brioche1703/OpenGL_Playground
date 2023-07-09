#pragma once

#include <glm/glm.hpp>

namespace Playground
{
	struct Material
	{
		glm::vec3 _ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
		glm::vec3 _diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
		glm::vec3 _specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
		float _shininess = 0.4f;
	};
}
