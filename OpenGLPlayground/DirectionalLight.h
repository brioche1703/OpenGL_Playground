#pragma once

#include <glm/glm.hpp>

#include "LightBase.h"

namespace Playground
{
struct DirectionalLight : public LightBase
{
public:
    DirectionalLight(const std::string &name)
        : LightBase(name)
    {}

    inline glm::vec3 &GetDirection() { return _direction; }

    inline void SetDirection(const glm::vec3 &direction) { _direction = direction; }

private:
    glm::vec3 _direction = glm::vec3(-0.2f, -1.0f, -0.3f);
};
} // namespace Playground
