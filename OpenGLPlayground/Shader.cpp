#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	void Shader::Delete()
	{
		glDeleteShader(_id);
	}
}