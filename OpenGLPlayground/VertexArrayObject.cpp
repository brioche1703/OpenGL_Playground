#include "VertexArrayObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &_id);
	}
	void VertexArrayObject::Bind()
	{
		glBindVertexArray(_id);
	}
	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArrayObject::Delete()
	{
		glDeleteVertexArrays(1, &_id);
	}
}
