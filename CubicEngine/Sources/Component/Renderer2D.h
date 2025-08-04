#pragma once

#include "Component.h"
#include "Renderer.h"
#include "../Object/GameObject.h"
#include "../Object/Material.h"
#include "../Object/Sprite.h"

namespace CubicEngine {

	class Renderer2D : public Renderer {
	public:
		Renderer2D();
		~Renderer2D();

		void* Clone_Obj() const override;
		Component* Clone_Comp() const override;
		Renderer2D* Clone() const;

		void Destroy() override;

		void Init() override;

		void Render(Camera* camera) override;

		void SetMaterial(Material* material);
		Material* GetMaterial() const;

		void SetSprite(Sprite sprite);
		Sprite GetSprite() const;

	private:
		Sprite sprite;

		Material* material;

		GLuint VAO, VBO, EBO;

		void UpdateBuffers();
	};
}