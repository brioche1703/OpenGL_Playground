#include "App.h"

#include <iostream>
#include <stdexcept>
#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Signal.h"
#include "RenderingPipeline.h"
#include "ImGuiController.h"
#include "BasicMultipleCubesRP.h"
#include "BasicLightRP.h"

namespace Playground
{
	App::App()
	{}

	App::~App()
	{
		_imguiController->Shutdown();
		delete _window;
		delete _input;
		delete _camera;
	}

	void App::Init()
	{
		_window = new Window();
		_imguiController = new ImGuiController(_window->GetWindowPtr());
		_camera = new Camera();
		_input = new Input(_window->GetWindowPtr());

		_input->ConnectCamera(_camera);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD";
		}

		_imguiController->Init();

		SetPipeline(_activePipelineId);

		glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
	}

	void App::GameLoop()
	{
		while (!_window->ShouldClose())
		{
			_input->ProcessInput();

			_imguiController->SetRender();
			ImGuiMenu();

			_activePipeline->Draw(_window, _camera);

			_imguiController->Render();

			glfwSwapBuffers(_window->GetWindowPtr());
			glfwPollEvents();
		}
		
		ClearActivePipeline();
	}

	void App::SetPipeline(const PipelineId newPipelineType)
	{
		DeleteActivePipeline();

		switch (newPipelineType)
		{
		case BASIC_LIGHT:
			_activePipeline = new BasicLightRP();
			break;
		case BASIC_MULTIPLE_CUBES:
			_activePipeline = new BasicMultipleCubesRP();
			break;
		}

		_activePipeline->Init();
		_activePipelineId = newPipelineType;
	}

	void App::ClearActivePipeline()
	{
		if (_activePipeline != nullptr)
		{
			_activePipeline->Clear();
		}
	}

	void App::DeleteActivePipeline()
	{
		if (_activePipeline != nullptr)
		{
			_activePipeline->Clear();
			delete _activePipeline;
		}
	}

	void App::ImGuiMenu()
	{
		ImGui::Begin("Settings");

		ImGui::Text("F1 : Toggle On/Off FPS camera");
		ImGui::Spacing();

		const char* pipelines[] = { "Basic Lighting", "Basic Multiple Cubes"};
		static int item_current = 0;
		ImGui::Combo("Rendering Pipeline", &item_current, pipelines, IM_ARRAYSIZE(pipelines));

		if (item_current != _activePipelineId)
		{
			SetPipeline((PipelineId)item_current);
		}

		ImGui::End();
	}
}
