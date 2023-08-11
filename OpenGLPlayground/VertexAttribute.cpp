#include "VertexAttribute.h"

namespace Playground
{
	VertexAttribute::VertexAttribute()
	{}

	void VertexAttribute::Enable(GLuint index)
	{
		glEnableVertexAttribArray(index);
	}
}
