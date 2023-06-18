#include "App.h"

#include <iostream>
#include <stdexcept>

#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "Buffer.h"
#include "VertexAttribute.h"
#include "VertexArrayObject.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "out vec4 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
		"FragColor = ourColor;\n"
	"}\0";

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
		float vertices[] = 
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left
		};

		unsigned int indices[] = 
		{
			0, 1, 3,
			1, 2, 3
		};

		VertexShader vertexShader(vertexShaderSource);
		FragmentShader fragmentShader(fragmentShaderSource);

		ShaderProgram shaderProgram;
		shaderProgram.AttachShader({ vertexShader, fragmentShader });
		shaderProgram.LinkProgram();

		vertexShader.Delete();
		fragmentShader.Delete();

		Buffer VBO, EBO;
		VertexArrayObject VAO;

		VAO.Bind();
		VBO.Bind(GL_ARRAY_BUFFER);
		VBO.Data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		VertexAttribute vertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		vertexAttrib.Enable(0);

		EBO.Bind(GL_ELEMENT_ARRAY_BUFFER);
		EBO.Data(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		while (!glfwWindowShouldClose(_window))
		{
			_input->ProcessInput();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shaderProgram.Use();
			float timeValue = glfwGetTime();
			float greenValue = sin(timeValue) / 2.0f + 0.5f;
			int vertexColorLocation = shaderProgram.GetUniformLocation("ourColor");
			shaderProgram.SetUniformLocation(glUniform4f, "ourColor", 0.0f, greenValue, 0.0f, 1.0f);

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
