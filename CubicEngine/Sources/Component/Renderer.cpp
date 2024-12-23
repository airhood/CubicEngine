#include "Renderer.h"

using namespace CubicEngine;

void Renderer::UseShader(Shader* shader, int pass) {
	glUseProgram(shader->passes[pass]->shaderProgram);
}

int Renderer::ShaderPassCount(Shader* shader) {
	return shader->passes.size();
}

void Renderer::BindTexture(GLenum target, Texture* texture) {
	glBindTexture(target, texture->gl_textureID);
}

void Renderer::SetRenderOrder(int value) {
	renderOrder = value;
	CORE->GET(RenderManager)->OnRenderOrderChanged();
}

int Renderer::GetRenderOrder() const {
	return renderOrder;
}