#include "Entity.h"

#include "EventSystem.h"

namespace Playground
{
Entity::Entity(const std::string &path)
    : _path(path)
{}

Entity::~Entity()
{
    EventSystem::GetInstance()->NotifyEntityRemoved(_path);
}
} // namespace Playground