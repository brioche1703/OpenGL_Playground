#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "Mesh2.h"

namespace Playground
{
	class ShaderProgram;
	class Model
	{
	public:
		Model(const std::string& path, bool gamma = false);
		void Draw(ShaderProgram& shaderProgram);

	private:
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh2 ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture2> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	private:
		std::vector<Texture2> _textures_loaded;
		std::vector<Mesh2> _meshes;
		std::string _directory;
		bool _gammaCorrection;
	};
}
