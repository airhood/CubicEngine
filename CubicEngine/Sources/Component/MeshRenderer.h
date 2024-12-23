#pragma once

#include "../Object/Mesh.h"
#include "../Object/Material.h"
#include "../Component/Component.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

namespace CubicEngine {
	class MeshRenderer : public Component, public Renderer {
	public:
		MeshRenderer() = default;
		~MeshRenderer();

		void Destroy() override;

		void SetMesh(Mesh* mesh);
		Mesh* GetMesh() const;
		
		void SetMaterial(Material* material);
		Material* GetMaterial() const;

		void Render(Camera* camera) override;

	private:
		Mesh* mesh;

		Material* material;

		GLuint VAO, VBO, EBO;

		void setupMesh();
	};
}