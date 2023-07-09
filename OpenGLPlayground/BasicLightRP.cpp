#include "BasicLightRP.h"

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
	void BasicLightRP::Init()
	{
		CubeMesh cube;

		// Cube
		VertexShader vertexShader("shaders/shader_vs.glsl");
		FragmentShader fragmentShader("shaders/phong_fs.glsl");

		_shaderProgram.AttachShader({ vertexShader, fragmentShader });
		_shaderProgram.LinkProgram();

		vertexShader.Delete();
		fragmentShader.Delete();

		_VAO.Bind();
		_VBO.Bind(GL_ARRAY_BUFFER);
		_VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormals(), &cube.GetVerticesWithNormals()[0], GL_STATIC_DRAW);
		VertexAttribute vertexAttrib;
		vertexAttrib.Set(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		vertexAttrib.Enable(0);
		vertexAttrib.Set(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		vertexAttrib.Enable(1);

		// Light
		VertexShader lightCubeVertexShader("shaders/shader_vs.glsl");
		FragmentShader lightCubeFragmentShader("shaders/LightCubeShader_fs.glsl");

		_lightCubeShaderProgram.AttachShader({ lightCubeVertexShader, lightCubeFragmentShader });
		_lightCubeShaderProgram.LinkProgram();

		lightCubeVertexShader.Delete();
		lightCubeFragmentShader.Delete();

		_VAOLight.Bind();

		_VBO.Bind(GL_ARRAY_BUFFER);
		_VBO.Data(GL_ARRAY_BUFFER, cube.GetSizeWithNormals(), &cube.GetVerticesWithNormals()[0], GL_STATIC_DRAW);
		VertexAttribute vertexAttribLight;
		vertexAttribLight.Set(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		vertexAttribLight.Enable(0);

		glEnable(GL_DEPTH_TEST);
	}

	void BasicLightRP::Draw(Window* window, Camera* camera)
	{
		glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		light._position = glm::vec3(cos(glfwGetTime()) * 3, 0.5f, sin(glfwGetTime()) * 3);

		// Cube
		glm::mat4 model(1.0f);
		glm::mat4 view = camera->LookAt();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera->GetFov()), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 100.0f);

		_shaderProgram.Use();
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
		_shaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));

		_shaderProgram.SetUniformLocation(glUniform3fv, "viewPosition", 1, glm::value_ptr(camera->GetPosition()));

		_shaderProgram.SetUniformLocation(glUniform3fv, "material.ambient", 1, glm::value_ptr(material._ambient));
		_shaderProgram.SetUniformLocation(glUniform3fv, "material.diffuse", 1, glm::value_ptr(material._diffuse));
		_shaderProgram.SetUniformLocation(glUniform3fv, "material.specular", 1, glm::value_ptr(material._specular));
		_shaderProgram.SetUniformLocation(glUniform1f, "material.shininess", material._shininess);

		_shaderProgram.SetUniformLocation(glUniform3fv, "light.position", 1, glm::value_ptr(light._position));
		_shaderProgram.SetUniformLocation(glUniform3fv, "light.ambient", 1, glm::value_ptr(light._ambient));
		_shaderProgram.SetUniformLocation(glUniform3fv, "light.diffuse", 1, glm::value_ptr(light._diffuse));
		_shaderProgram.SetUniformLocation(glUniform3fv, "light.specular", 1, glm::value_ptr(light._specular));

		_VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Light object
		model = glm::translate(model, light._position);
		model = glm::scale(model, glm::vec3(0.2f));

		_lightCubeShaderProgram.Use();
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "view", 1, GL_FALSE, glm::value_ptr(view));
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "projection", 1, GL_FALSE, glm::value_ptr(projection));
		_lightCubeShaderProgram.SetUniformLocation(glUniformMatrix4fv, "model", 1, GL_FALSE, glm::value_ptr(model));
		_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "light.ambient", 1, glm::value_ptr(light._ambient));
		_lightCubeShaderProgram.SetUniformLocation(glUniform3fv, "light.diffuse", 1, glm::value_ptr(light._diffuse));

		_VAOLight.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void BasicLightRP::Clear()
	{

		_VAO.Delete();
		_VBO.Delete();
		_shaderProgram.Delete();
	}
}
