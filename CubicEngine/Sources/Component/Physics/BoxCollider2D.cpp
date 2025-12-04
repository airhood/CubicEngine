#include "BoxCollider2D.h"

using namespace CubicEngine;

void BoxCollider2D::Destroy() {

}

void* BoxCollider2D::Clone_Obj() const {
	return Clone();
}

Component* BoxCollider2D::Clone_Comp() const {
	return Clone();
}

BoxCollider2D* BoxCollider2D::Clone() const {
	// TODO: BoxCollider2D clone
	return nullptr;
}