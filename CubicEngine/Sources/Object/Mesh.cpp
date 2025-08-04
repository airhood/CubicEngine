#include "Mesh.h"

using namespace CubicEngine;

void Mesh::Destroy() {

}

void* Mesh::Clone_Obj() const {
	return Clone();
}

Mesh* Mesh::Clone() const {
	Mesh* mesh = new Mesh();
	mesh->vertices = vertices;
	mesh->indices = indices;
	mesh->textures = textures;
	return mesh;
}