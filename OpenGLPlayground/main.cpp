#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.h"
#include "Input.h"
#include "RenderingPipeline.h"
#include "BasicMultipleCubesRP.h"

using namespace Playground;

int main()
{
	App app;
	app.Init();

	BasicMultipleCubesRP* pipeline = new BasicMultipleCubesRP();
	app.AttachRenderingPipeline(pipeline);

	app.GameLoop();

	glfwTerminate();
	return 0;
}