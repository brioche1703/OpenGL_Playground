#pragma once

#include <vector>

namespace Playground
{
	class Mesh
	{
	public:
		Mesh() {};
		Mesh(const std::vector<float>& vertices) : _vertices(vertices) {}

		const std::vector<float>& GetVertices() { return _vertices; }
		size_t GetSize() { return sizeof(float) * _vertices.size(); };

		const std::vector<float>& GetVerticesWithNormals() { return _verticesWithNormals; }
		size_t GetSizeWithNormals() { return sizeof(float) * _verticesWithNormals.size(); };

	protected:
		std::vector<float> _vertices;
		std::vector<float> _verticesWithNormals;
	};
}

