#pragma once

#include "ShaderProgram.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Playground
{

#define MAX_BONE_INFLUENCE 4

	struct Vertex
	{
		glm::vec3 _position;
		glm::vec3 _normal;
		glm::vec2 _texCoords;

		glm::vec3 _tangent;
		glm::vec3 _bitangent;

		int _boneIDs[MAX_BONE_INFLUENCE];
		float _weights[MAX_BONE_INFLUENCE];
	};

	struct Texture2
	{
		unsigned int _id;
		std::string _type;
		std::string _path;
	};

	class Mesh2
	{
	public:
		Mesh2(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2> textures);

		void Draw(ShaderProgram& shaderProgram);

	private:
		void SetupMesh();

	private:
		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
		std::vector<Texture2> _textures;

		unsigned int _VAO, _VBO, _EBO;
	};
}
