#pragma once

#include <glm.hpp>
#include <vector>
#include "Texture.h"
#include "Material.h"

#define MAX_BONE_INFLUENCE 4

namespace CubicEngine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		//bone indexes which will influence this vertex
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	class Mesh {
	public:
		Mesh() = default;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;
	};
}