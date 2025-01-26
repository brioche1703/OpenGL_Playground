#include "EventSystem.h"

namespace Playground
{

EventSystem *EventSystem::_eventSystem = nullptr;

void EventSystem::RegisterEntityCreatedCallback(const EntityCreatedCallback &callback)
{
    _entityCreatedCallbacks.push_back(callback);
}

void EventSystem::RegisterEntityRemovedCallback(const EntityRemovedCallback &callback)
{
    _entityRemovedCallbacks.push_back(callback);
}

void EventSystem::NotifyEntityCreated(const std::string &path, std::shared_ptr<Entity> entity)
{
    for (const auto &callback : _entityCreatedCallbacks)
    {
        callback(path, entity);
    }
}
void EventSystem::NotifyEntityRemoved(const std::string &path)
{
    for (const auto &callback : _entityRemovedCallbacks)
    {
        callback(path);
    }
}
} // namespace Playground
