#include "Entity.h"

#include "EventSystem.h"

namespace Playground
{
Entity::Entity(const std::string &name)
    : _name(name)
{}

Entity::~Entity()
{
    EventSystem::GetInstance()->NotifyEntityRemoved(_name);
}
} // namespace Playground