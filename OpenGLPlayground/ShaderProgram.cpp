#include "ShaderProgram.h"

#include <iostream>

#include "Shader.h"

namespace Playground
{
	ShaderProgram::ShaderProgram()
	{
		_id = glCreateProgram();
	}
	void ShaderProgram::AttachShader(Shader shader)
	{
		glAttachShader(_id, shader.Id());
	}
	void ShaderProgram::AttachShader(std::vector<Shader> shaders)
	{
		for (Shader shader : shaders)
		{
			AttachShader(shader);
		}
	}
	int ShaderProgram::GetUniformLocation(const std::string& name) const
	{
		return glGetUniformLocation(_id, name.c_str());
	}
	void ShaderProgram::LinkProgram()
	{
		glLinkProgram(_id);

		int success;
		char infoLog[512];
		glGetProgramiv(_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(_id, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	void ShaderProgram::Use()
	{
		glUseProgram(_id);
	}
	void ShaderProgram::Delete()
	{
		glDeleteProgram(_id);
	}
}
