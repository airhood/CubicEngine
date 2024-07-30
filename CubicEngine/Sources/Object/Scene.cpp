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
	for (auto game_object : game_objects) {
		game_object->Init();
	}
}

void Scene::PhysicsTick(float elapsedTime) {
	for (auto game_object : game_objects) {
		game_object->PhysicsTick(elapsedTime);
	}
}

void Scene::FrameTick(float elapsedTime) {
	for (auto game_object : game_objects) {
		game_object->FrameTick(elapsedTime);
	}
}

void Scene::LateTick(float elapsedTime) {
	for (auto game_object : game_objects) {
		game_object->LateTick(elapsedTime);
	}
}

void Scene::AddGameObject(GameObject* game_object) {
	game_objects.push_back(game_object);
}

GameObject* Scene::GetGameObjectByName(std::string name) {
	for (auto& game_object : game_objects) {
		if (game_object->GetName() == name) return game_object;
	}
	return nullptr;
}

GameObject* Scene::GetGameObjectByID(std::string id) {
	for (auto& game_object : game_objects) {
		if (game_object->GetObjectID() == id) return game_object;
	}
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectByTag(std::string tag)
{
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagExists(tag)) return game_object;
	}
	return nullptr;
}

GameObject* CubicEngine::Scene::GetGameObjectByTags(std::initializer_list<std::string> tags)
{
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagsExists(tags)) return game_object;
	}
	return nullptr;
}

std::vector<GameObject*> CubicEngine::Scene::GetGameObjectsByName(std::string name)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->GetName() == name) results.push_back(game_object);
	}
	return results;
}

std::vector<GameObject*> CubicEngine::Scene::GetGameObjectsByTag(std::string tag)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagExists(tag)) results.push_back(game_object);
	}
	return results;
}

std::vector<GameObject*> CubicEngine::Scene::GetGameObjectsByTags(std::initializer_list<std::string> tags)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagsExists(tags)) results.push_back(game_object);
	}
	return results;
}
