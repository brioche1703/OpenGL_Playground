#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.h"

using namespace Playground;

int main()
{
	App app;
	app.Init();

	app.GameLoop();

	glfwTerminate();
	return 0;
}