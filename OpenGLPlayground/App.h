#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Playground
{
class Window;
class Input;
class Camera;
class RenderingPipeline;
class ImGuiController;

class App
{
private:
    enum PipelineId
    {
        BASIC_LIGHT = 0,
        BASIC_MULTIPLE_CUBES = 1,
        LIGHTING_MAPS = 2,
        LIGHT_CASTERS = 3,
        MODEL_LOADING = 4,
        MODEL_LOADING_LIT = 5,
    };

public:
    App() noexcept;
    App(const App &other) = delete;
    void operator=(const App &other) = delete;
    ~App();

    void Init();
    void GameLoop();

private:
    void SetPipeline(const PipelineId newPipeline);
    void ClearActivePipeline();

    void ImGuiMenu();

private:
    PipelineId _activePipelineId = MODEL_LOADING_LIT;

    std::unique_ptr<Window> _window;
    std::unique_ptr<ImGuiController> _imguiController;
    std::unique_ptr<Input> _input;
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<RenderingPipeline> _activePipeline;
};
} // namespace Playground
