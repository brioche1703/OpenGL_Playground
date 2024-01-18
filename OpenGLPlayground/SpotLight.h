#pragma once

#include <glm/glm.hpp>

namespace Playground
{
struct SpotLight
{
    glm::vec3 _position = glm::vec3(0.0f);
    glm::vec3 _direction = glm::vec3(0.2f);
    float _cutOffAngle = glm::cos(glm::radians(4.0f));
    float _outerCutOffAngle = glm::cos(glm::radians(4.0f));

    glm::vec3 _ambient = glm::vec3(0.2f);
    glm::vec3 _diffuse = glm::vec3(0.5f);
    glm::vec3 _specular = glm::vec3(1.0f);

    float _constant = 1.0f;
    float _linear = 0.09f;
    float _quadratic = 0.032f;
};
} // namespace Playground
