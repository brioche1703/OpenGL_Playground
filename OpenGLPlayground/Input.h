#pragma once

#include "Signal.h"

struct GLFWwindow;

namespace Playground
{
class Camera;

class Input
{
  public:
    Input(GLFWwindow *window);
    Input(Input &other) = delete;
    void operator=(const Input &other) = delete;

    static Input *GetInstance();

    void ProcessInput();
    void ConnectCamera(Camera *const camera);

  private:
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void MouseCallback(GLFWwindow *window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

  public: // SIGNALS
    Signal<int> OnInputPressed;
    Signal<double, double> OnMouseMove;
    Signal<double> OnMouseScroll;

  private:
    GLFWwindow *_window = nullptr;

    float _lastMouseX = 0.0f;
    float _lastMouseY = 0.0f;
    float _sensitivity = 0.1f;
    bool _firstMouse = true;
    bool _fpsMode = false;
};

} // namespace Playground
