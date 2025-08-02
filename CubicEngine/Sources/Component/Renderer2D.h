#pragma once

#include "Component.h"
#include "Renderer.h"
#include "../Object/GameObject.h"
#include "../Object/Material.h"

namespace CubicEngine {

	class Sprite;

	class Renderer2D : public Renderer {
	public:
		Renderer2D();
		~Renderer2D();

		void* Clone_Obj() override;

		Component* Clone_Comp() override;

		void Destroy() override;

		void Init() override;

		void Render(Camera* camera) override;

		void SetMaterial(Material* material);
		Material* GetMaterial() const;

	public:
		Sprite* sprite;

	private:
		Material* material;

		GLuint VAO, VBO, EBO;
	};
}