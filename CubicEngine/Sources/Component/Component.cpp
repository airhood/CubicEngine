#include "Component.h"

using namespace CubicEngine;

int Component::SceneNum() {
	return scene_num;
}

GameObject* Component::RootGameObject() {
	return root_game_object;
}

int Component::AddGameInstance(GameInstance* game_instance) {
	game_instances.push_back(game_instance);
	return game_instances.size() - 1;
}

std::vector<GameInstance*> Component::GetGameInstances() {
	return game_instances;
}

GameInstance* Component::GetGameInstance(int instance_num) {
	return game_instances[instance_num];
}

int Component::InstanceCount() {
	return game_instances.size();
}