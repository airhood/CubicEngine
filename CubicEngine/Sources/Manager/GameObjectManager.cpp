#include "GameObjectManager.h"

using namespace CubicEngine;

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::Init()
{

}

void GameObjectManager::Exterminate()
{

}

void GameObjectManager::AddGameObject(int scene_num, GameObject* game_object)
{
	CORE->GET(SceneManager)->getScene(scene_num)->AddGameObject(game_object);
}

GameObject* GameObjectManager::GetGameObjectByName(int scene_num, std::string name)
{
	return CORE->GET(SceneManager)->getCurrentScene()->GetGameObjectByName(name);
}

GameObject* GameObjectManager::GetGameObjectByID(int scene_num, std::string id)
{
	return nullptr;
}

GameObject* GameObjectManager::GetGameObjectByTag(int scene_num, std::string tag)
{
	return nullptr;
}

GameObject* GameObjectManager::GetGameObjectByTags(int scene_num, std::initializer_list<std::string> tags)
{
	return nullptr;
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByName(int scene_num, std::string name)
{
	return std::vector<GameObject*>();
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByTag(int scene_num, std::string tag)
{
	return std::vector<GameObject*>();
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByTags(int scene_num, std::initializer_list<std::string> tags)
{
	return std::vector<GameObject*>();
}
