#pragma once

#include <string>
#include <functional>
#include <memory>

namespace Playground
{
class Entity;
class EventSystem
{
public:
    using EntityCreatedCallback = std::function<void(const std::string &, std::shared_ptr<Entity>)>;
    using EntityRemovedCallback = std::function<void(const std::string &)>;

protected:
    EventSystem() = default;

public:
    EventSystem(const EventSystem &other) = delete;
    EventSystem &operator=(const EventSystem &other) = delete;

    static EventSystem* GetInstance()
    {
        if (_eventSystem == nullptr)
        {
            _eventSystem = new EventSystem();
        }
        return _eventSystem;
    }

    void RegisterEntityCreatedCallback(const EntityCreatedCallback &callback);
    void RegisterEntityRemovedCallback(const EntityRemovedCallback &callback);
    void NotifyEntityCreated(const std::string &path, std::shared_ptr<Entity> entity);
    void NotifyEntityRemoved(const std::string &path);

private:
    static EventSystem* _eventSystem;
    std::vector<EntityCreatedCallback> _entityCreatedCallbacks;
    std::vector<EntityRemovedCallback> _entityRemovedCallbacks;
};
} // namespace Playground
