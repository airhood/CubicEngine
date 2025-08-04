#include "Component.h"
#include "../Object/GameObject.h"

using namespace CubicEngine;

void* Component::Clone_Obj() const {
	return Clone_Comp();
}

GameObject* Component::RootGameObject() {
	return root_game_object;
}

int Component::RootSceneNum() {
	return root_game_object->RootSceneNum();
}

int Component::CurrentSceneNum() {
	return CORE->GET(SceneManager)->GetCurrentSceneNum();
}