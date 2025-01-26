#pragma once

#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Playground
{
class Entity;
class EventSystem;
class GarbageCollection
{
protected:
	GarbageCollection();

public:
    GarbageCollection(const EventSystem &other) = delete;
    GarbageCollection &operator=(const GarbageCollection &other) = delete;

    static GarbageCollection* GetInstance();
    const std::map<std::string, std::shared_ptr<Entity>>& GetEntities() const;

    void CollectGarbage();

private:
    void OnEntityCreated(const std::string& path, std::shared_ptr<Entity> entity);

private:
    static GarbageCollection* _garbageCollection;
    int _minEntities = 5;
    std::map<std::string, std::shared_ptr<Entity>> _entities;
};

} // namespace Playground
