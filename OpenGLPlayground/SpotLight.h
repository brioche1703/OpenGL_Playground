#pragma once

#include <glm/glm.hpp>

#include "LightBase.h"

namespace Playground
{
class SpotLight : public LightBase
{
public:
    SpotLight(const std::string &name)
        : LightBase(name)
    {}

    inline glm::vec3 &GetDirection() { return _direction; }
    inline float &GetCutOffAngle() { return _cutOffAngle; }
    inline float &GetOuterCutOffAngle() { return _outerCutOffAngle; }

    inline void SetDirection(const glm::vec3 &direction) { _direction = direction; }
    inline void SetCutOffAngle(float cutOffAngle) { _cutOffAngle = cutOffAngle; }
    inline void SetOuterCutOffAngle(float outerCutOffAngle) { _outerCutOffAngle = outerCutOffAngle; }

private:
    glm::vec3 _direction = glm::vec3(0.2f);
    float _cutOffAngle = glm::cos(glm::radians(4.0f));
    float _outerCutOffAngle = glm::cos(glm::radians(4.0f));
};
} // namespace Playground
