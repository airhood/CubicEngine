#include "Mesh.h"

using namespace CubicEngine;

void Mesh::Destroy() {

}

void* Mesh::Clone_Obj() {
	return Clone();
}

Mesh* Mesh::Clone() {
	Mesh* mesh = new Mesh();
	mesh->vertices = vertices;
	mesh->indices = indices;
	mesh->textures = textures;
	return mesh;
}