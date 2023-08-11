#include "LightCastersRP.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <stbi/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "VertexAttribute.h"
#include "Texture.h"
#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Signal.h"
#include "CubeMesh.h"
#include "Material.h"

namespace Playground
{
	void LightCastersRP::Init()
	{
		CubeMesh cube;

		// Cube
		VertexShader vertexShader("shaders/shader_vs.glsl");
		FragmentShader fragmentShader("shaders/phong_lightCasters_fs.glsl");

		_shaderProgram.AttachShader({ vertexShader, fragmentShader });
		_shaderProgram.LinkProgram();

		vertexShader.Delete();
		fragmentShader.Delete();

		_VAO.Bind();
		_VBO.Bind(GL_ARRAY_BUFFER);
		_VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormalsAndTexCoords(), &cube.GetVerticesWithNormalsAndTexCoords()[0], GL_STATIC_DRAW);
		VertexAttribute vertexAttrib;
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		vertexAttrib.Enable(0);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		vertexAttrib.Enable(1);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		vertexAttrib.Enable(2);

		// Lights
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

		VertexShader lightCubeVertexShader("shaders/shader_vs.glsl");
		FragmentShader lightCubeFragmentShader("shaders/LightCubeShader_fs.glsl");

		_lightCubeShaderProgram.AttachShader({ lightCubeVertexShader, lightCubeFragmentShader });
		_lightCubeShaderProgram.LinkProgram();

		lightCubeVertexShader.Delete();
		lightCubeFragmentShader.Delete();

		_VAOLight.Bind();

		_VBO.Bind(GL_ARRAY_BUFFER);
		_VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormalsAndTexCoords(), &cube.GetVerticesWithNormalsAndTexCoords()[0], GL_STATIC_DRAW);
		VertexAttribute vertexAttribLight;
		vertexAttribLight.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		vertexAttribLight.Enable(0);

		glEnable(GL_DEPTH_TEST);
	}

	void LightCastersRP::Draw(Window* window, Camera* camera)
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
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));

		_shaderProgram.SetUniformLocation(glUniform3fv, "viewPosition", 1, glm::value_ptr(camera->GetPosition()));

		_shaderProgram.SetUniformLocation(glUniform1i, "material.diffuse", 0);
		_shaderProgram.SetUniformLocation(glUniform1i, "material.specular", 1);
		_shaderProgram.SetUniformLocation(glUniform1i, "material.emissive", 2);
		_shaderProgram.SetUniformLocation(glUniform3fv, "material.specular", 1, glm::value_ptr(_material._specular));
		_shaderProgram.SetUniformLocation(glUniform1f, "material.shininess", _material._shininess);

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

		_textureContainer.Activate(GL_TEXTURE0);
		_textureContainer.Bind();
		_textureContainerSpecular.Activate(GL_TEXTURE1);
		_textureContainerSpecular.Bind();
		_textureContainerEmissive.Activate(GL_TEXTURE2);
		_textureContainerEmissive.Bind();

		_VAO.Bind();

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Light object
		for (size_t i = 0; i < _pointLights.size(); i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, _pointLights[i]._position);
			model = glm::scale(model, glm::vec3(0.2f));

			_lightCubeShaderProgram.Use();
			_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
			_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
			_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
			_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.position", 1, glm::value_ptr(_pointLights[i]._position));
			_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.ambient", 1, glm::value_ptr(_pointLights[i]._ambient));
			_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.diffuse", 1, glm::value_ptr(_pointLights[i]._diffuse));

			_VAOLight.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void LightCastersRP::Clear()
	{

		_VAO.Delete();
		_VBO.Delete();
		_shaderProgram.Delete();
	}
}
