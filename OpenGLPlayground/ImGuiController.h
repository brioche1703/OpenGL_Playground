#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace Playground
{
class ImGuiController
{
public:
    ImGuiController(GLFWwindow *window);

    void Init();
    void SetRender();
    void Render();
    void Shutdown();

private:
    GLFWwindow *_window = nullptr;
};
} // namespace Playground
