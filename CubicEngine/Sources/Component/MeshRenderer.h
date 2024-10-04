#pragma once

#include "../Util/Mesh.h"
#include <GLFW/glfw3.h>

namespace CubicEngine {
	class MeshRenderer {
	public:

		void SetMesh(Mesh mesh);
		void Draw();

	private:
		Mesh mesh;

		unsigned int VAO, VBO, EBO;

		void setupMesh();
	};
}