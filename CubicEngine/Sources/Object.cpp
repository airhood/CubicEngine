#include "Object.h"

using namespace CubicEngine;

Object::Object() {

}

Object::~Object() = default;

std::string Object::GetObjectID() const {
	return objectID;
}

void Object::Destroy() {

}
