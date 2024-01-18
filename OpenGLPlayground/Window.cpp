#include "Window.h"

namespace Playground
{

Window::Window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(_width, _height, "My OpenGL Sandbox", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        throw "Failed to create GLFW window";
    }
    else
    {
        _window = window;
    }

    glfwMakeContextCurrent(_window);

    auto framebuffer_size_callback = [](GLFWwindow *window, int width, int height) {
        FramebufferSizeCallback(window, width, height);
    };
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(_window);
}

void Window::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

} // namespace Playground
