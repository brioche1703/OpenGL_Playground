#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "App.h"
#include "Input.h"
#include "RenderingPipeline.h"
#include "BasicMultipleCubesRP.h"
#include "BasicLightRP.h"

using namespace Playground;

int main()
{
	App app;
	app.Init();

	BasicLightRP* pipeline = new BasicLightRP();
	app.AttachRenderingPipeline(pipeline);

	app.GameLoop();

	glfwTerminate();
	return 0;
}