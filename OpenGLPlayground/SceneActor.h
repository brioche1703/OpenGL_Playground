#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

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

    inline const glm::mat4 GetModelMatrix() const
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, _position);
        model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, _scale);
        return model;
    }

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
};
} // namespace Playground
