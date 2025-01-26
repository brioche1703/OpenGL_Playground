#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{

class Window
{
public:
    Window();
    ~Window();
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    inline GLFWwindow *GetWindowPtr() const { return _window; };
    inline int GetWidth() const { return _width; }
    inline int GetHeight() const { return _height; }

    bool ShouldClose() const;

private:
    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

private:
    int _width = 1600;
    int _height = 1200;

    GLFWwindow *_window = nullptr;
};

} // namespace Playground
