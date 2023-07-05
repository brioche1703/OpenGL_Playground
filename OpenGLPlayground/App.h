#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	class Window;
	class Input;
	class Camera;
	class RenderingPipeline;

	class App
	{
	public:
		App();
		~App();

		void Init();
		void GameLoop();
		void AttachRenderingPipeline(RenderingPipeline* renderingPipeline);
		void DetachRenderingPipeline();

	private:
		Window* _window = nullptr;
		Input* _input = nullptr;
		Camera* _camera = nullptr;
		RenderingPipeline* _pipeline = nullptr;
	};
}

