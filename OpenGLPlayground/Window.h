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
		float GetFov() { return _fov; }

		bool ShouldClose();

	private:
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	private:
		int _width = 800;
		int _height = 600;
		float _fov = 45.0f;

		GLFWwindow* _window = nullptr;
	};

}
