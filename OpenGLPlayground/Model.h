#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Mesh.h"

namespace Playground
{
class Texture;
class ShaderProgram;
class Model
{
  public:
    Model(const std::string &path, bool gamma = false);
    ~Model();

    void Draw(ShaderProgram &shaderProgram);

  private:
    void LoadModel(std::string path);
    void ProcessNode(aiNode *node, const aiScene *scene);
    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

  private:
    std::vector<Texture> _textures_loaded;
    std::vector<Mesh> _meshes;
    std::string _directory;
    bool _gammaCorrection;
};
} // namespace Playground
