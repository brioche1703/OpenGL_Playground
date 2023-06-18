#pragma once

struct GLFWwindow;

namespace Playground
{
	class Input
	{
	public:
		Input(GLFWwindow* window);

		void ProcessInput();

	private:
		GLFWwindow* _window;
	};

}
