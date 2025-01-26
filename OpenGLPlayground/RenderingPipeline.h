#pragma once

#include <memory>

namespace Playground
{

class Window;
class Camera;
class App;

class RenderingPipeline
{
public:
    virtual ~RenderingPipeline() = default;
    virtual void Init() = 0;
    virtual void Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera) = 0;
    virtual void Clear() = 0;
    virtual void ImGuiMenu() {}; 
};

} // namespace Playground
