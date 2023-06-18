#pragma once

namespace Playground
{
	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		void Bind();
		void Unbind();
		void Delete();

	private:
		unsigned int _id;
	};

}
