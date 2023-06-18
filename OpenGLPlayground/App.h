#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"

namespace Playground
{
	class App
	{
	public:
		App();
		void Init();
		void GameLoop();

		GLFWwindow* GetWindow() const { return _window; }

	private:
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);


	private:
		Input* _input = nullptr;
		GLFWwindow* _window = nullptr;
	};
}

