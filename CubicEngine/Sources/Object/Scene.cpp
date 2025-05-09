#include "Scene.h"

using namespace CubicEngine;

Scene::Scene() {
	game_objects.push_back(new GameObject());
}

Scene::~Scene() {

}

void Scene::Destroy() {

}

void* Scene::Clone_Obj() {
	return Clone();
}

Scene* Scene::Clone() {
	Scene* scene = new Scene();
	scene->name = name;
	for (auto* game_object : game_objects) {
		scene->game_objects.push_back(game_object->Clone());
	}
	return scene;
}

void Scene::SetName(std::string name) {
	this->name = name;
}

std::string Scene::GetName() {
	return name;
}

void Scene::AddGameObject(GameObject* game_object) {
	game_object->root_scene_num = scene_num;
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

GameObject* Scene::GetGameObjectByTag(std::string tag)
{
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagExists(tag)) return game_object;
	}
	return nullptr;
}

GameObject* Scene::GetGameObjectByTags(std::initializer_list<std::string> tags)
{
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagsExists(tags)) return game_object;
	}
	return nullptr;
}

std::vector<GameObject*> Scene::GetAllGameObjects() {
	return game_objects;
}

std::vector<GameObject*> Scene::GetGameObjectsByName(std::string name)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->GetName() == name) results.push_back(game_object);
	}
	return results;
}

std::vector<GameObject*> Scene::GetGameObjectsByTag(std::string tag)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagExists(tag)) results.push_back(game_object);
	}
	return results;
}

std::vector<GameObject*> Scene::GetGameObjectsByTags(std::initializer_list<std::string> tags)
{
	std::vector<GameObject*> results;
	for (auto& game_object : game_objects) {
		if (game_object->CheckTagsExists(tags)) results.push_back(game_object);
	}
	return results;
}
