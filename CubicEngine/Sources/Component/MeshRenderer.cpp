#include "MeshRenderer.h"

using namespace CubicEngine;

MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Destroy() {

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
