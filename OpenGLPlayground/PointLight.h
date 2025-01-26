#pragma once

#include <glm/glm.hpp>

#include "LightBase.h"

namespace Playground
{
class PointLight : public LightBase
{
public:
    PointLight(const std::string &name)
        : LightBase(name)
    {}
    PointLight(const std::string &name, const glm::vec3& position)
        : LightBase(name)
    {
        SetPosition(position);
    }
};
} // namespace Playground
