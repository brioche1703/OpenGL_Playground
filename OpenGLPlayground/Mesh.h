#pragma once

#include "ShaderProgram.h"

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "VertexArrayObject.h"
#include "Buffer.h"
#include "Texture.h"

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

class Mesh
{
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures,
         float shininess = 64.0f);

    void Draw(ShaderProgram &shaderProgram);

  private:
    void SetupMesh();

  private:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;
    float _shininess = 64.0f;

    VertexArrayObject _VAO;
    Buffer _VBO, _EBO;
};
} // namespace Playground
