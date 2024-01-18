#include "Model.h"

#include <iostream>
#include <stbi\stb_image.h>

#include "ShaderProgram.h"
#include "Texture.h"

namespace Playground
{
Model::Model(const std::string &path, bool gamma)
    : _gammaCorrection(gamma)
{
    LoadModel(path);
}

Model::~Model()
{
    std::vector<unsigned int> indices;
    std::transform(_textures_loaded.begin(), _textures_loaded.end(), std::back_inserter(indices),
                   [](Texture t) { return t.GetID(); });
    glDeleteTextures(_textures_loaded.size(), &indices[0]);
}

void Model::Draw(ShaderProgram &shaderProgram)
{
    for (unsigned int i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].Draw(shaderProgram);
    }
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
                                                       aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    _directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        // position
        glm::vec3 vector{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex._position = vector;

        // normals
        if (mesh->HasNormals())
        {
            vector = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
            vertex._normal = vector;
        }

        // texture coordinates
        if (mesh->mTextureCoords[0])
        {
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            glm::vec2 vec = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            vertex._texCoords = vec;

            // tangent
            vector = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
            vertex._tangent = vector;

            // bitangent
            vector = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
            vertex._bitangent = vector;
        }
        else
        {
            vertex._texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex
    // indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string fullPath = _directory + '/' + str.C_Str();
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < _textures_loaded.size(); j++)
        {
            if (std::strcmp(_textures_loaded[j].GetPath().data(), fullPath.c_str()) == 0)
            {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture =
                Texture(_directory + '/' + std::string(str.C_Str()), GL_TEXTURE_2D, true, GL_REPEAT, typeName);

            textures.push_back(texture);

            // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
            _textures_loaded.push_back(texture);
        }
    }
    return textures;
}
} // namespace Playground
