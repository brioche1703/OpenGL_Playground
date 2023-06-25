#include "App.h"

#include <iostream>
#include <stdexcept>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "VertexAttribute.h"
#include "VertexArrayObject.h"
#include "Texture.h"

namespace Playground
{
	App::App()
	{}

	void App::Init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Sandbox", NULL, NULL);
		if (window == NULL)
		{
			glfwTerminate();
			throw "Failed to create GLFW window";
		}
		else
		{
			_window = window;
		}

		glfwMakeContextCurrent(_window);

		_input = new Input(_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD";
		}

		glViewport(0, 0, 800, 600);
		auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) { FramebufferSizeCallback(window, width, height); };
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	}

	void App::GameLoop()
	{
		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};
		
		unsigned int indices[] = 
		{
			0, 1, 3,
			1, 2, 3, 
		};

		VertexShader vertexShader("shaders/shader_vs.glsl");
		FragmentShader fragmentShader("shaders/shader_fs.glsl");

		ShaderProgram shaderProgram;
		shaderProgram.AttachShader({ vertexShader, fragmentShader });
		shaderProgram.LinkProgram();

		vertexShader.Delete();
		fragmentShader.Delete();

		Buffer VBO, EBO;
		VertexArrayObject VAO;

		Texture texture1("images/container.jpg", GL_TEXTURE_2D);
		Texture texture2("images/smiley.png", GL_TEXTURE_2D, true);

		VAO.Bind();
		VBO.Bind(GL_ARRAY_BUFFER);
		VBO.Data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		VertexAttribute vertexAttrib;
		vertexAttrib.Set(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		vertexAttrib.Enable(0);
		vertexAttrib.Set(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		vertexAttrib.Enable(1);
		vertexAttrib.Set(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		vertexAttrib.Enable(2);

		EBO.Bind(GL_ELEMENT_ARRAY_BUFFER);
		EBO.Data(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		while (!glfwWindowShouldClose(_window))
		{
			_input->ProcessInput();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));

			shaderProgram.Use();
			shaderProgram.SetUniformLocation(glUniform1i, "texture1", 0);
			shaderProgram.SetUniformLocation(glUniform1i, "texture2", 1);
			shaderProgram.SetUniformLocation(glUniformMatrix4fv, "transform", 1, GL_FALSE, glm::value_ptr(transform));

			texture1.Activate(GL_TEXTURE0);
			texture1.Bind();
			texture2.Activate(GL_TEXTURE1);
			texture2.Bind();

			VAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(_window);
			glfwPollEvents();
		}

		VAO.Delete();
		VBO.Delete();
		shaderProgram.Delete();

	}

	void App::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
