#include "Input.h"

#include <GLFW/glfw3.h>

#include "Camera.h"


namespace Playground
{
	static Input* _instance = nullptr;

	Input::Input(GLFWwindow* window)
		:
		_window(window)
	{
		if (_instance == nullptr)
		{
			_instance = this;
		}

		glfwSetInputMode(_window, GLFW_CURSOR, _fpsMode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		glfwSetKeyCallback(_window, KeyCallback);
		glfwSetCursorPosCallback(_window, MouseCallback);
		glfwSetScrollCallback(_window, ScrollCallback);
	}

	Input* Input::GetInstance()
	{
		return _instance;
	}

	void Input::ProcessInput()
	{
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_W);
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_S);
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_A);
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_D);
		}
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_Q);
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_E);
		}
		if (glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS && _fpsMode)
		{
			_instance->OnInputPressed.Emit(GLFW_KEY_R);
		}
	}

	void Input::ConnectCamera(Camera* const camera)
	{
		OnInputPressed.ConnectMember(camera, &Camera::OnInputReceive);
		OnMouseMove.ConnectMember(camera, &Camera::ProcessMouseOffset);
		OnMouseScroll.ConnectMember(camera, &Camera::Zoom);
	}

	// This callback processes only one input event
	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		else if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		{
			_instance->_fpsMode = !_instance->_fpsMode;
			glfwSetInputMode(window, GLFW_CURSOR, _instance->_fpsMode ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}
	}

	void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (_instance->_firstMouse)
		{
			_instance->_lastMouseX = (float)xpos;
			_instance->_lastMouseY = (float)ypos;
			_instance->_firstMouse = false;
		}

		float xOffset = (float)xpos - _instance->_lastMouseX;
		float yOffset = _instance->_lastMouseY - (float)ypos;
		_instance->_lastMouseX = (float)xpos;
		_instance->_lastMouseY = (float)ypos;

		xOffset *= _instance->_sensitivity;
		yOffset *= _instance->_sensitivity;

		if (_instance->_fpsMode)
		{
			_instance->OnMouseMove.Emit(xOffset, yOffset);
		}
	}

	void Input::ScrollCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (_instance->_fpsMode)
		{
			_instance->OnMouseScroll.Emit(ypos);
		}
	}
}
