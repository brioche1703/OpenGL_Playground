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

namespace Playground
{
	void ModelLoadingLitRP::Init()
	{
		glEnable(GL_DEPTH_TEST);

		VertexShader vertexShader("shaders/modelLoading_vs.glsl");
		FragmentShader fragmentShader("shaders/modelLoadingLit_fs.glsl");

		_shaderProgram.AttachShader({ vertexShader, fragmentShader });
		_shaderProgram.LinkProgram();

		_model = new Model("models/backpack/backpack.obj");

		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f, 0.2f, 2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f, 2.0, -12.0),
			glm::vec3(0.0f, 0.0f, -3.0f)
		};

		glm::vec3 pointLightColors[] = {
			glm::vec3(1.0f, 0.6f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0, 0.0),
			glm::vec3(0.2f, 0.2f, 1.0f)
		};

		_pointLights.push_back(PointLight(pointLightPositions[0], pointLightColors[0], pointLightColors[0], pointLightColors[0]));
		_pointLights.push_back(PointLight(pointLightPositions[1], pointLightColors[1], pointLightColors[1], pointLightColors[1]));
		_pointLights.push_back(PointLight(pointLightPositions[2], pointLightColors[2], pointLightColors[2], pointLightColors[2]));
		_pointLights.push_back(PointLight(pointLightPositions[3], pointLightColors[3], pointLightColors[3], pointLightColors[3]));

		vertexShader.Delete();
		fragmentShader.Delete();
	}

	void ModelLoadingLitRP::Draw(Window* window, Camera* camera)
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_spotLight._position = camera->GetPosition();
		_spotLight._direction = camera->GetFront();

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

		_shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.direction", 1, glm::value_ptr(_directionalLight._direction));
		_shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.ambient", 1, glm::value_ptr(_directionalLight._ambient));
		_shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.diffuse", 1, glm::value_ptr(_directionalLight._diffuse));
		_shaderProgram.SetUniformLocation(glUniform3fv, "directionalLight.specular", 1, glm::value_ptr(_directionalLight._specular));

		_shaderProgram.SetUniformLocation(glUniform1i, "numberOfPointLight", (GLint)_pointLights.size());

		for (int i = 0; i < _pointLights.size(); i++)
		{
			_shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "].position", 1, glm::value_ptr(_pointLights[i]._position));
			_shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "].ambient", 1, glm::value_ptr(_pointLights[i]._ambient));
			_shaderProgram.SetUniformLocation(glUniform3fv, "pointLight[" + std::to_string(i) + "].diffuse", 1, glm::value_ptr(_pointLights[i]._diffuse));
			_shaderProgram.SetUniformLocation(glUniform3fv, "pointLights[" + std::to_string(i) + "]specular", 1, glm::value_ptr(_pointLights[i]._specular));
			_shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].constant", _pointLights[i]._constant);
			_shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].linear", _pointLights[i]._linear);
			_shaderProgram.SetUniformLocation(glUniform1f, "pointLights[" + std::to_string(i) + "].quadratic", _pointLights[i]._quadratic);
		}

		_shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.position", 1, glm::value_ptr(_spotLight._position));
		_shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.direction", 1, glm::value_ptr(_spotLight._direction));
		_shaderProgram.SetUniformLocation(glUniform1f, "spotLight.cutOffAngle", _spotLight._cutOffAngle);
		_shaderProgram.SetUniformLocation(glUniform1f, "spotLight.outerCutOffAngle", _spotLight._outerCutOffAngle);
		_shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.ambient", 1, glm::value_ptr(_spotLight._ambient));
		_shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.diffuse", 1, glm::value_ptr(_spotLight._diffuse));
		_shaderProgram.SetUniformLocation(glUniform3fv, "spotLight.specular", 1, glm::value_ptr(_spotLight._specular));
		_shaderProgram.SetUniformLocation(glUniform1f, "spotLight.constant", _spotLight._constant);
		_shaderProgram.SetUniformLocation(glUniform1f, "spotLight.linear", _spotLight._linear);
		_shaderProgram.SetUniformLocation(glUniform1f, "spotLight.quadratic", _spotLight._quadratic);

		_model->Draw(_shaderProgram);
	}

	void ModelLoadingLitRP::Clear()
	{
		_shaderProgram.Delete();
		delete _model;
	}
}
