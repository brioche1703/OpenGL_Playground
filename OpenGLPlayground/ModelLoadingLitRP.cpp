#include "ModelLoadingLitRP.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Signal.h"
#include "LightSystem.h"

namespace Playground
{
	void ModelLoadingLitRP::Init()
	{
		glEnable(GL_DEPTH_TEST);

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f, 0.2f, 2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f, 2.0, -12.0),
			glm::vec3(0.0f, 0.0f, -3.0f)
		};

		glm::vec3 pointLightColors[] = {
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0, 0.0),
			glm::vec3(1.0f, 0.0f, 0.0f)
		};

		std::vector<PointLight> pointLights;
		pointLights.reserve(pointLightPositions->length());
		pointLights.push_back(PointLight(pointLightPositions[0], pointLightColors[0], pointLightColors[0], pointLightColors[0]));
		pointLights.push_back(PointLight(pointLightPositions[1], pointLightColors[1], pointLightColors[1], pointLightColors[1]));
		pointLights.push_back(PointLight(pointLightPositions[2], pointLightColors[2], pointLightColors[2], pointLightColors[2]));
		pointLights.push_back(PointLight(pointLightPositions[3], pointLightColors[3], pointLightColors[3], pointLightColors[3]));

		_lightSystem = new LightSystem(pointLights);

		VertexShader vertexShader("shaders/modelLoading_vs.glsl");
		FragmentShader fragmentShader("shaders/modelLoadingLit_fs.glsl");

		_shaderProgram.AttachShader({ vertexShader, fragmentShader });
		_shaderProgram.LinkProgram();

		_model = new Model("models/backpack/backpack.obj");

		vertexShader.Delete();
		fragmentShader.Delete();

		_lightSystem->Init();
	}

	void ModelLoadingLitRP::Draw(Window* window, Camera* camera)
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Cube
		glm::mat4 model(1.0f);
		glm::mat4 view = camera->LookAt();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera->GetFov()), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

		_shaderProgram.Use();
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
		_shaderProgram.SetUniformLocation(glUniform3fv, "viewPosition", 1, glm::value_ptr(camera->GetPosition()));

		_lightSystem->SetUniforms(_shaderProgram, view, projection);

		_model->Draw(_shaderProgram);

		_lightSystem->DrawLightsObjects(view, projection);
	}

	void ModelLoadingLitRP::Clear()
	{
		_shaderProgram.Delete();
		delete _model;
	}

	ModelLoadingLitRP::~ModelLoadingLitRP() 
	{
		delete _model; 
		delete _lightSystem;

		_model = nullptr;
		_lightSystem = nullptr;
	}
}
