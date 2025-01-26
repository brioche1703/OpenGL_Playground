#pragma once

#include <string>
#include <memory>

#include "EventSystem.h"
#include "GarbageCollection.h"

namespace Playground
{
class RefCounter
{
public:
    std::shared_ptr<RefCounter> GetShared()
    {
        return _self.lock();
    }

protected:
    RefCounter() = default;
    virtual ~RefCounter() = default;
    RefCounter(const RefCounter &) = delete;
    RefCounter &operator=(const RefCounter &) = delete;

    void InitializeSelf(std::shared_ptr<RefCounter> self)
    {
        _self = self;
    }

private:
    std::weak_ptr<RefCounter> _self;
}; 

class Entity : public RefCounter
{
public:
    template <typename T, typename... Args>
    static std::shared_ptr<T> Create(const std::string& name, Args&&... args);

    virtual ~Entity();

protected:
    Entity(const std::string &name);

protected:
    std::string _name;
};

template <typename T, typename... Args> 
std::shared_ptr<T> Entity::Create(const std::string& name, Args &&...args)
{
    // Check if entity already exists
    const std::map<std::string, std::shared_ptr<Entity>>& entityMap = GarbageCollection::GetInstance()->GetEntities();
    auto it = entityMap.find(name);
    if (it != entityMap.end())
    {
        return std::static_pointer_cast<T>(it->second);
    }

    auto entity = std::shared_ptr<T>(new T(name, std::forward<Args>(args)...));
    entity->InitializeSelf(entity);
    EventSystem::GetInstance()->NotifyEntityCreated(entity->_name, entity);
    return entity;
}
} // namespace Playground
