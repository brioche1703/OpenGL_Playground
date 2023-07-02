#pragma once

struct GLFWwindow;

namespace Playground
{
	class Camera;

	class Input
	{
	public:
		Input(GLFWwindow* window, Camera* camera);
		Input(Input& other) = delete;
		void operator=(const Input& other) = delete;

		static Input* GetInstance();

		void ProcessInput();

	private:
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	private:
		GLFWwindow* _window = nullptr;
		Camera* _camera = nullptr;

		float _deltaTime = 0.0f;
		float _lastFrameTime = 0.0f;

		float _lastMouseX = 0.0f;
		float _lastMouseY = 0.0f;
		float _sensitivity = 0.1f;
		bool _firstMouse = true;
	};

}
