#include "CircleCollider.h"

using namespace CubicEngine;

void CircleCollider::Destroy() {

}

void* CircleCollider::Clone_Obj() const {
	return Clone();
}

Component* CircleCollider::Clone_Comp() const {
	return Clone();
}

CircleCollider* CircleCollider::Clone() const {
	CircleCollider* circleCollider = new CircleCollider();
	circleCollider->radius = this->radius;
	circleCollider->offset = this->offset;
	return circleCollider;
}