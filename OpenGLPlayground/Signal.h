#pragma once

#include <functional>
#include <map>

namespace Playground
{
template <typename... Args> class Signal
{
  public:
    Signal() = default;
    ~Signal() = default;
    Signal(const Signal &) = delete;

    Signal &operator=(const Signal &other)
    {
        if (this != &other)
        {
            DisconnectAll();
        }
        return *this;
    }

    Signal(Signal &&other) noexcept : _slots(std::move(other._slots)), _currentId(other._currentId)
    {
    }

    Signal &operator=(Signal &&other)
    {
        if (this != &other)
        {
            _slots = std::move(other._slots);
            _currentId = other._currentId;
        }
        return *this;
    }

    int Connect(const std::function<void(Args...)> &slot) const
    {
        _slots.insert(std::make_pair(++_currentId, slot));
        return _currentId;
    }

    template <typename T> int ConnectMember(T *inst, void (T::*func)(Args...))
    {
        return Connect([=](Args... args) { (inst->*func)(args...); });
    }

    void Disconnect(int id) const
    {
        _slots.erase(id);
    }

    void DisconnectAll(int id) const
    {
        _slots.clear;
    }

    void Emit(Args... params)
    {
        for (auto const &it : _slots)
        {
            it.second(params...);
        }
    }

    void EmitForAllButOne(int excludedConnectionID, Args... params)
    {
        for (auto const &it : _slots)
        {
            if (it.first != excludedConnectionID)
            {
                it.second(params...);
            }
        }
    }

    void EmitFor(int connectionID, Args... params)
    {
        auto const &it = _slots.find(connectionID);
        if (it != _slots.end())
        {
            it.second(params...);
        }
    }

  private:
    mutable std::map<int, std::function<void(Args...)>> _slots;
    mutable int _currentId = 0;
};
} // namespace Playground
