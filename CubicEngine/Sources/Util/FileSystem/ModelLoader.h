#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include "../Mesh.h"
#include "../Logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace CubicEngine {
	class ModelLoader {
	public:
		static std::vector<Mesh> LoadModel(std::string path);

	private:
		static std::vector<Mesh> ProcessNode(aiNode* node, const aiScene* scene,
			std::vector<Texture>& textures_loaded, std::string directory);
		static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene,
			std::vector<Texture>& textures_loaded, std::string directory);
		static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
			std::string typeName, std::vector<Texture>& textures_loaded, std::string directory);
		static unsigned int TextureFromFile(const char* path, const std::string& directory);
	};
}