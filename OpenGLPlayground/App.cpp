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

		glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
	}

	void App::GameLoop()
	{
		while (!_window->ShouldClose())
		{
			_input->ProcessInput();
			_imguiController->SetRender();

			if (_pipeline)
			{
				_pipeline->Draw(_window, _camera);
			}

			_imguiController->Render();

			glfwSwapBuffers(_window->GetWindowPtr());
			glfwPollEvents();
		}
		
		DetachRenderingPipeline();
	}

	void App::AttachRenderingPipeline(RenderingPipeline* renderingPipeline)
	{
		_pipeline = renderingPipeline;

		if (_pipeline)
		{
			_pipeline->Init();
		}
	}

	void App::DetachRenderingPipeline()
	{
		if (_pipeline)
		{
			_pipeline->Clear();
			_pipeline = nullptr;
		}
	}
}
