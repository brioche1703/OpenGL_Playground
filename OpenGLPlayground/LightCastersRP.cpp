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
		vertexAttrib.Set(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		vertexAttrib.Enable(0);
		vertexAttrib.Set(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		vertexAttrib.Enable(1);
		vertexAttrib.Set(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		vertexAttrib.Enable(2);

		// Light
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
		vertexAttribLight.Set(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		vertexAttribLight.Enable(0);

		glEnable(GL_DEPTH_TEST);
	}

	void LightCastersRP::Draw(Window* window, Camera* camera)
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const float radius = 6.0f;
		//_pointLight._position = glm::vec3(cos(glfwGetTime()) * radius, 0.5f, sin(glfwGetTime()) * radius);
		_pointLight._position = glm::vec3(-4.0f, 0.5f, 0.5f);

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

		_shaderProgram.SetUniformLocation(glUniform3fv, "pointLight.position", 1, glm::value_ptr(_pointLight._position));
		_shaderProgram.SetUniformLocation(glUniform3fv, "pointLight.ambient", 1, glm::value_ptr(_pointLight._ambient));
		_shaderProgram.SetUniformLocation(glUniform3fv, "pointLight.diffuse", 1, glm::value_ptr(_pointLight._diffuse));
		_shaderProgram.SetUniformLocation(glUniform3fv, "pointLight.specular", 1, glm::value_ptr(_pointLight._specular));
		_shaderProgram.SetUniformLocation(glUniform1f, "pointLight.constant", _pointLight._constant);
		_shaderProgram.SetUniformLocation(glUniform1f, "pointLight.linear", _pointLight._linear);
		_shaderProgram.SetUniformLocation(glUniform1f, "pointLight.quadratic", _pointLight._quadratic);

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
		model = glm::translate(model, _pointLight._position);
		model = glm::scale(model, glm::vec3(0.2f));

		_lightCubeShaderProgram.Use();
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
		_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.position", 1, glm::value_ptr(_pointLight._position));
		_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.ambient", 1, glm::value_ptr(_pointLight._ambient));
		_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "pointLight.diffuse", 1, glm::value_ptr(_pointLight._diffuse));

		_VAOLight.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void LightCastersRP::Clear()
	{

		_VAO.Delete();
		_VBO.Delete();
		_shaderProgram.Delete();
	}
}
