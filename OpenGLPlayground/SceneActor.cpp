#include "SceneActor.h"

namespace Playground
{
SceneActor::SceneActor(const std::string path)
    : Entity(path)
    , _position(glm::vec3(0.0f))
    , _rotation(glm::vec3(0.0f))
    , _scale(glm::vec3(1.0f))
{}
} // namespace Playground