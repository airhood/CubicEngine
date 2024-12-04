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

Mesh* MeshRenderer::GetMesh() {
	return mesh;
}

void MeshRenderer::SetMaterial(Material* material) {
	this->material = material;
}

Material* MeshRenderer::GetMaterial() {
	return material;
}

void MeshRenderer::Render() {

}

void MeshRenderer::setupMesh() {

}
