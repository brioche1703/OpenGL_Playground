#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace Playground
{
	class Window;
	class Input;
	class Camera;
	class RenderingPipeline;
	class ImGuiController;

	class App
	{
	private:
		enum PipelineId	 
		{
			BASIC_LIGHT = 0,
			BASIC_MULTIPLE_CUBES = 1,
			LIGHTING_MAPS = 2,
			LIGHT_CASTERS = 3,
			MODEL_LOADING = 4,
		};

	public:
		App();
		~App();

		void Init();
		void GameLoop();
	private:
		void SetPipeline(const PipelineId newPipeline);
		void ClearActivePipeline();
		void DeleteActivePipeline();

		void ImGuiMenu();

	private:
		Window* _window = nullptr;
		ImGuiController* _imguiController = nullptr;
		Input* _input = nullptr;
		Camera* _camera = nullptr;

		PipelineId _activePipelineId = MODEL_LOADING;
		RenderingPipeline* _activePipeline = nullptr;
	};
}

