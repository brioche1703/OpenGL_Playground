#pragma once

#include <glm/glm.hpp>

#include "Entity.h"

namespace Playground
{
class SceneActor : public Entity
{
public:
    SceneActor(const std::string path);

    inline void SetPosition(const glm::vec3 &position) { _position = position; }
    inline void SetRotation(const glm::vec3 &rotation) { _rotation = rotation; }
    inline void SetScale(const glm::vec3 &scale) { _scale = scale; }

    inline const glm::vec3 &GetPosition() const { return _position; }
    inline const glm::vec3 &GetRotation() const { return _rotation; }
    inline const glm::vec3 &GetScale() const { return _scale; }

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
};
} // namespace Playground
