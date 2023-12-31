#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{

	class Window
	{
	public:
		Window();

		GLFWwindow* GetWindowPtr() { return _window; };
		int GetWidth() { return _width; }
		int GetHeight() { return _height; }

		bool ShouldClose();

	private:
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		int _width = 1600;
		int _height = 1200;

		GLFWwindow* _window = nullptr;
	};

}
