#include "Mesh.h"

#include <glad/glad.h>

#include "ShaderProgram.h"
#include "VertexAttribute.h"

namespace Playground
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
		:
		_vertices(vertices),
		_indices(indices),
		_textures(textures)
	{
		SetupMesh();
	}

	void Mesh::Draw(ShaderProgram& shaderProgram)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < _textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			std::string name = _textures[i].GetType();
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
			}
			else if (name == "texture_normal")
			{
				number = std::to_string(normalNr++);
			}
			else if (name == "texture_height")
			{
				number = std::to_string(heightNr++);
			}

			shaderProgram.SetUniformLocation(glUniform1i, (name + number), i);

			_textures[i].Bind();
		}

		_VAO.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetupMesh()
	{
		_VAO.Bind();
		_VBO.Bind(GL_ARRAY_BUFFER);
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

		_EBO.Bind(GL_ELEMENT_ARRAY_BUFFER);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

		VertexAttribute vertexAttrib;
		vertexAttrib.Enable(0);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		vertexAttrib.Enable(1);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _normal));
		vertexAttrib.Enable(2);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _texCoords));
		vertexAttrib.Enable(3);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _tangent));
		vertexAttrib.Enable(4);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _bitangent));
		vertexAttrib.Enable(5);
		vertexAttrib.SetAttributePointer(glVertexAttribIPointer, 5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, _boneIDs));
		vertexAttrib.Enable(6);
		vertexAttrib.SetAttributePointer(glVertexAttribPointer, 6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _weights));

		glBindVertexArray(0);
	}
}
