#include "App.h"

#include <stbi/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BasicLightRP.h"
#include "BasicMultipleCubesRP.h"
#include "Camera.h"
#include "ImGuiController.h"
#include "Input.h"
#include "LightCastersRP.h"
#include "LightingMapsRP.h"
#include "ModelLoadingLitRP.h"
#include "ModelLoadingRP.h"
#include "RenderingPipeline.h"
#include "Window.h"

namespace Playground
{
App::~App()
{
    _imguiController->Shutdown();
    delete _window;
    delete _input;
    delete _camera;
}

void App::Init()
{
    _window = new Window();
    _imguiController = new ImGuiController(_window->GetWindowPtr());
    _camera = new Camera();
    _input = new Input(_window->GetWindowPtr());

    _input->ConnectCamera(_camera);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw "Failed to initialize GLAD";
    }

    _imguiController->Init();

    SetPipeline(_activePipelineId);

    glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
}

void App::GameLoop()
{
    while (!_window->ShouldClose())
    {
        _input->ProcessInput();

        _imguiController->SetRender();
        ImGuiMenu();

        _activePipeline->Draw(_window, _camera);

        _imguiController->Render();

        glfwSwapBuffers(_window->GetWindowPtr());
        glfwPollEvents();
    }

    ClearActivePipeline();
}

void App::SetPipeline(const PipelineId newPipelineType)
{
    DeleteActivePipeline();

    switch (newPipelineType)
    {
    case BASIC_LIGHT:
        _activePipeline = new BasicLightRP();
        break;
    case BASIC_MULTIPLE_CUBES:
        _activePipeline = new BasicMultipleCubesRP();
        break;
    case LIGHTING_MAPS:
        _activePipeline = new LightingMaps();
        break;
    case LIGHT_CASTERS:
        _activePipeline = new LightCastersRP();
        break;
    case MODEL_LOADING:
        _activePipeline = new ModelLoadingRP();
        break;
    case MODEL_LOADING_LIT:
        _activePipeline = new ModelLoadingLitRP();
        break;
    default:
        _activePipeline = new LightCastersRP();
        break;
    }

    _activePipeline->Init();
    _activePipelineId = newPipelineType;
}

void App::ClearActivePipeline()
{
    if (_activePipeline != nullptr)
    {
        _activePipeline->Clear();
    }
}

void App::DeleteActivePipeline()
{
    if (_activePipeline != nullptr)
    {
        _activePipeline->Clear();
        delete _activePipeline;
    }
}

void App::ImGuiMenu()
{
    ImGui::Begin("Settings");

    ImGui::Text("F1 : Toggle On/Off FPS camera");
    ImGui::Spacing();

    const char *pipelines[] = {"Basic Lighting", "Basic Multiple Cubes", "Lighting Maps",
                               "Light Casters",  "Model Loading Unlit",  "Model Loading Lit"};
    static int item_current = _activePipelineId;
    ImGui::Combo("Rendering Pipeline", &item_current, pipelines, IM_ARRAYSIZE(pipelines));

    if (item_current != _activePipelineId)
    {
        SetPipeline((PipelineId)item_current);
    }

    ImGui::End();
}
} // namespace Playground
