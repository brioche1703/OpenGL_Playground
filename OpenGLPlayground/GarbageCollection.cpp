#include "GarbageCollection.h"

#include "Model.h"
#include "EventSystem.h"

namespace Playground
{
GarbageCollection *GarbageCollection::_garbageCollection = nullptr;

GarbageCollection::GarbageCollection()
{
    EventSystem::GetInstance()->RegisterEntityCreatedCallback(
        [this](const std::string &path, std::shared_ptr<Entity> entity) { OnEntityCreated(path, entity); });
}

GarbageCollection *GarbageCollection::GetInstance()
{
    if (_garbageCollection == nullptr)
    {
        _garbageCollection = new GarbageCollection();
    }
    return _garbageCollection;
}

const std::map<std::string, std::shared_ptr<Entity>> &GarbageCollection::GetEntities() const
{
    return _entities;
}

void GarbageCollection::CollectGarbage()
{
    if (_entities.size() <= _minEntities)
    {
        return;
    }
    
    auto it = _entities.begin();
    std::advance(it, _minEntities);

    for (; it != _entities.end();) 
    {
        if (it->second.use_count() == 1)
        {
            it = _entities.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GarbageCollection::OnEntityCreated(const std::string &path, std::shared_ptr<Entity> entity)
{
    _entities[path] = entity;
}

} // namespace Playground