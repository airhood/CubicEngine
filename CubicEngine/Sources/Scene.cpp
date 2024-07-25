#include "Scene.h"

using namespace CubicEngine;

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Init() {
	InitGameObjects();
}

void Scene::InitGameObjects() {
	for (auto gameObject : game_objects) {
		gameObject->Init();
	}
}

void Scene::Tick(float elapsedTime) {
	for (auto gameObject : game_objects) {
		gameObject->Tick(elapsedTime);
	}
}

GameObject* Scene::GetGameObjectByName(std::string name) {
	auto it = std::find_if(game_objects.begin(), game_objects.end(), [name](const GameObject* element) { return element->GetName() == name; });
	if (it != game_objects.end()) {
		return *it;
	}
	return nullptr;
}

GameObject* Scene::GetGameObjectByID(std::string id) {
	auto it = std::find_if(game_objects.begin(), game_objects.end(), [id](const GameObject* element) { return element->GetObjectID() == id; });
	if (it != game_objects.end()) {
		return *it;
	}
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectByTag(std::string tag)
{
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectByTags(std::initializer_list<std::string> tags)
{
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectsByName(std::string name)
{
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectsByTag(std::string tag)
{
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectsByTags(std::initializer_list<std::string> tags)
{
	return nullptr;
}
