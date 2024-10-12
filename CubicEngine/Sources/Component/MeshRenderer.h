#pragma once

#include "../Object/Mesh.h"
#include "../Object/Material.h"
#include <GLFW/glfw3.h>

namespace CubicEngine {
	class MeshRenderer {
	public:

		void SetMesh(Mesh* mesh);
		Mesh* GetMesh();
		
		void SetMaterial(Material* material);
		Material* GetMaterial();

		void Draw();

	private:
		Mesh* mesh;

		Material* material;

		unsigned int VAO, VBO, EBO;

		void setupMesh();
	};
}