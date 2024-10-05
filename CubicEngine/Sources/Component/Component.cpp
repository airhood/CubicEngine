#include "Component.h"

using namespace CubicEngine;

void Component::Destroy() {

}

void* Component::Clone_Obj() {
	return Clone();
}

Component* Component::Clone() {
	Component* clone = new Component();
	return clone;
}

int Component::SceneNum() {
	return scene_num;
}

GameObject* Component::RootGameObject() {
	return root_game_object;
}