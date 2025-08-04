#include "MeshRenderer.h"

using namespace CubicEngine;

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Destroy() {

}

void* MeshRenderer::Clone_Obj() const {
	return Clone();
}

Component* MeshRenderer::Clone_Comp() const {
	return Clone();
}

MeshRenderer* MeshRenderer::Clone() const {
	// TODO: implement MeshRenderer clone
	return nullptr;
}

void MeshRenderer::SetMesh(Mesh* mesh) {
	this->mesh = mesh;
	setupMesh();
}

Mesh* MeshRenderer::GetMesh() const {
	return mesh;
}

void MeshRenderer::SetMaterial(Material* material) {
	this->material = material;
}

Material* MeshRenderer::GetMaterial() const {
	return material;
}

void MeshRenderer::Render(Camera* camera) {

}

void MeshRenderer::setupMesh() {

}
