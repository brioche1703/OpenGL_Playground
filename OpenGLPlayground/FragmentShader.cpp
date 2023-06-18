#include "FragmentShader.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	FragmentShader::FragmentShader(const char* source)
	{
		_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_id, 1, &source, NULL);
		glCompileShader(_id);
		int success;
		char infoLog[512];
		glGetShaderiv(_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
}
