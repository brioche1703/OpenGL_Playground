#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	class Window;
	class Input;
	class Camera;

	class App
	{
	public:
		App();
		~App();
		void Init();
		void GameLoop();

	private:
		Window* _window = nullptr;
		Input* _input = nullptr;
		Camera* _camera = nullptr;
	};
}

