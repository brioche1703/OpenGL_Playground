#include "Input.h"

#include <GLFW/glfw3.h>

#include "Camera.h"

namespace Playground
{
	static Input* _instance = nullptr;

	Input::Input(GLFWwindow* window, Camera* camera)
		:
		_window(window),
		_camera(camera)
	{
		if (_instance == nullptr)
		{
			_instance = this;
		}

		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(_window, MouseCallback);
		glfwSetScrollCallback(_window, ScrollCallback);
	}

	Input* Input::GetInstance()
	{
		return _instance;
	}

	void Input::ProcessInput()
	{
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, true);
		}

		// Camera
		float currentFrameTime = glfwGetTime();
		_deltaTime = currentFrameTime - _lastFrameTime;
		_lastFrameTime = currentFrameTime;

		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			_camera->Move(Camera::FORWARD, _deltaTime);
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			_camera->Move(Camera::BACKWARD, _deltaTime);
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			_camera->Move(Camera::LEFT, _deltaTime);
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			_camera->Move(Camera::RIGHT, _deltaTime);
		}
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			_camera->Move(Camera::DOWN, _deltaTime);
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
		{
			_camera->Move(Camera::UP, _deltaTime);
		}
	}
	void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (_instance->_firstMouse)
		{
			_instance->_lastMouseX = xpos;
			_instance->_lastMouseY = ypos;
			_instance->_firstMouse = false;
		}

		float xOffset = xpos - _instance->_lastMouseX;
		float yOffset = _instance->_lastMouseY - ypos;
		_instance->_lastMouseX = xpos;
		_instance->_lastMouseY = ypos;

		xOffset *= _instance->_sensitivity;
		yOffset *= _instance->_sensitivity;

		_instance->_camera->ProcessMouseOffset(xOffset, yOffset);
	}
	void Input::ScrollCallback(GLFWwindow* window, double xpos, double ypos)
	{
		_instance->_camera->Zoom(ypos);
	}
}
