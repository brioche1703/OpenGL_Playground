#include "Input.h"

#include <GLFW/glfw3.h>

namespace Playground
{
	Input::Input(GLFWwindow* window)
		:
		_window(window)
	{}

	void Input::ProcessInput()
	{
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, true);
		}
	}
}
