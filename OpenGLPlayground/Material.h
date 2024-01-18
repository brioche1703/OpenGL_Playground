#pragma once

#include <glm/glm.hpp>

namespace Playground
{
struct Material
{
    glm::vec3 _ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 _diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 _specular = glm::vec3(1.0f, 1.0f, 1.0f);
    float _shininess = 64.0f;
};
} // namespace Playground
