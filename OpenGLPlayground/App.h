#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	class Window;
	class Input;

	class App
	{
	public:
		App();
		~App();
		void Init();
		void GameLoop();

	private:
		Input* _input = nullptr;
		Window* _window = nullptr;
	};
}

