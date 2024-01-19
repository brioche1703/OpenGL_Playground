#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace Playground
{
Camera::Camera()
{}

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : _pos(pos)
    , _front(front)
    , _up(up)
{}

glm::mat4 Camera::LookAt() const
{
    return glm::lookAt(_pos, _pos + _front, _up);
}

void Camera::Move(Movement movement)
{
    double currentFrameTime = glfwGetTime();
    _deltaTime = currentFrameTime - _lastFrameTime;
    _lastFrameTime = currentFrameTime;

    switch (movement)
    {
    case FORWARD:
        _pos += _speed * _front;
        break;
    case BACKWARD:
        _pos -= _speed * _front;
        break;
    case LEFT:
        _pos -= _speed * GetRightVector();
        break;
    case RIGHT:
        _pos += _speed * GetRightVector();
        break;
    case UP:
        _pos += _speed * _up;
        break;
    case DOWN:
        _pos -= _speed * _up;
        break;
    }
}

void Camera::ProcessMouseOffset(const double xOffset, const double yOffset)
{
    _yaw += (float)xOffset;
    _pitch += (float)yOffset;

    if (_pitch > 89.0f)
    {
        _pitch = 89.0f;
    }
    if (_pitch < -89.0f)
    {
        _pitch = -89.0f;
    }

    glm::vec3 newDirection(cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)), sin(glm::radians(_pitch)),
                           sin(glm::radians(_yaw)) * cos(glm::radians(_pitch)));

    _front = glm::normalize(newDirection);
}

void Camera::Zoom(const double yOffset)
{
    _fov -= (float)yOffset;
    if (_fov < 1.0f)
    {
        _fov = 1.0f;
    }
    else if (_fov > 45.0f)
    {
        _fov = 45.0f;
    }
}

void Camera::Reset()
{
    *this = Camera();
}

void Camera::OnInputReceive(int key)
{
    switch (key)
    {
    case GLFW_KEY_W:
        Move(FORWARD);
        break;
    case GLFW_KEY_S:
        Move(BACKWARD);
        break;
    case GLFW_KEY_A:
        Move(LEFT);
        break;
    case GLFW_KEY_D:
        Move(RIGHT);
        break;
    case GLFW_KEY_E:
        Move(UP);
        break;
    case GLFW_KEY_Q:
        Move(DOWN);
        break;
    case GLFW_KEY_R:
        Reset();
        break;
    }
}

glm::vec3 Camera::GetRightVector() const
{
    return glm::normalize(glm::cross(_front, _up));
}
} // namespace Playground
