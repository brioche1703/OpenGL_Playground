#include "VertexAttribute.h"

namespace Playground
{
	VertexAttribute::VertexAttribute()
	{}
	void VertexAttribute::Set(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	void VertexAttribute::Enable(GLuint index)
	{
		glEnableVertexAttribArray(index);
	}
}
