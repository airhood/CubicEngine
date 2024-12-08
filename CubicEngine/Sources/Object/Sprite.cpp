#include "Sprite.h"

using namespace CubicEngine;

Sprite::~Sprite() {
	Destroy();
}

void Sprite::Destroy() {

}

void* Sprite::Clone_Obj() {
	return Clone();
}

Sprite* Sprite::Clone() {
	Sprite* sprite = new Sprite();
	sprite->texture = texture;
	return sprite;
}