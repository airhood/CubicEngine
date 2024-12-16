#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../Object/Shader.h"
#include "../Object/Texture.h"

namespace CubicEngine {
	class Renderer abstract {
	protected:
		Renderer() = default;
		virtual ~Renderer() = default;

		static void UseShader(Shader* shader, int pass);
		static int ShaderPassCount(Shader* shader);
		static void BindTexture(GLenum target, Texture* texture);

	public:
		virtual void Render(Camera* camera) = 0;

		void SetRenderOrder(int value);

		int GetRenderOrder() const;

	private:
		int renderOrder = 0;
	};
}