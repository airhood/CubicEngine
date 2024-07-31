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
	CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectByName(name);
}

GameObject* GameObjectManager::GetGameObjectByID(int scene_num, std::string id)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectByID(id);
}

GameObject* GameObjectManager::GetGameObjectByTag(int scene_num, std::string tag)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectByTag(tag);
}

GameObject* GameObjectManager::GetGameObjectByTags(int scene_num, std::initializer_list<std::string> tags)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectByTags(tags);
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByName(int scene_num, std::string name)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectsByName(name);
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByTag(int scene_num, std::string tag)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectsByTag(tag);
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsByTags(int scene_num, std::initializer_list<std::string> tags)
{
	return CORE->GET(SceneManager)->getScene(scene_num)->GetGameObjectsByTags(tags);
}
