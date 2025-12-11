#pragma once

#include "../../Object/Mesh.h"
#include "../../Object/Material.h"
#include "../../Component/Component.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

namespace CubicEngine {
	class MeshRenderer : public Renderer {
	public:
		MeshRenderer();
		~MeshRenderer();

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		MeshRenderer* Clone() const;

		void Destroy() override;

		void Init() override;

		void SetMesh(Mesh* mesh);
		Mesh* GetMesh() const;
		
		void SetMaterial(Material* material);
		Material* GetMaterial() const;

		void Render(Camera* camera) override;

		void UpdateMesh() const;

	private:
		Mesh* mesh;

		Material* material;

		GLuint VAO, VBO, EBO;

		void SetupMesh();
	};
}