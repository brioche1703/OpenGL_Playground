#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	class VertexAttribute
	{
	public:
		VertexAttribute();

		void Set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer = (void*)0);
		void Enable(GLuint index);
	};
}

