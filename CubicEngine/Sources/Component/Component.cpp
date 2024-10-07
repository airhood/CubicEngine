#include "Component.h"

using namespace CubicEngine;

int Component::SceneNum() {
	return scene_num;
}

GameObject* Component::RootGameObject() {
	return root_game_object;
}