#include "Component.h"

using namespace CubicEngine;

void* Component::Clone_Obj() {
	return Clone_Comp();
}

int Component::SceneNum() {
	return scene_num;
}

GameObject* Component::RootGameObject() {
	return root_game_object;
}