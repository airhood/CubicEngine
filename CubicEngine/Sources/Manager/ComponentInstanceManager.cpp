#include "ComponentInstanceManager.h"
#include "../Object/Scene.h"

using namespace CubicEngine;

ComponentInstanceManager::~ComponentInstanceManager() {
	Exterminate();
}

void ComponentInstanceManager::Init() {

}

void ComponentInstanceManager::Start() {
	Scene* current_scene = CORE->GET(SceneManager)->GetCurrentScene();
	if (current_scene == nullptr) return;
	for (auto* game_object : current_scene->GetAllGameObjects()) {
		if (game_object == nullptr) continue;
		CallStart(game_object);
	}
}

void ComponentInstanceManager::PhysicsTick(float elapsed_time) {
	Scene* current_scene = CORE->GET(SceneManager)->GetCurrentScene();
	if (current_scene == nullptr) return;
	for (auto* game_object : current_scene->GetAllGameObjects()) {
		if (game_object == nullptr) continue;
		CallPhysicsTick(elapsed_time, game_object);
	}
}

void ComponentInstanceManager::FrameTick(float elapsed_time) {
	Scene* current_scene = CORE->GET(SceneManager)->GetCurrentScene();
	if (current_scene == nullptr) return;
	for (auto& game_object : current_scene->GetAllGameObjects()) {
		if (game_object == nullptr) continue;
		CallFrameTick(elapsed_time, game_object);
	}
}

void ComponentInstanceManager::LateTick(float elapsed_time) {
	Scene* current_scene = CORE->GET(SceneManager)->GetCurrentScene();
	if (current_scene == nullptr) return;
	for (auto* game_object : current_scene->GetAllGameObjects()) {
		if (game_object == nullptr) continue;
		CallLateTick(elapsed_time, game_object);
	}
}

void ComponentInstanceManager::Exterminate() {

}

void ComponentInstanceManager::CallStart(GameObject* game_object) {
	for (auto& component : game_object->GetAllComponents()) {
		if (component == nullptr) continue;
		component->Start();
	}
	
	for (auto& child : game_object->GetChildren()) {
		if (child == nullptr) continue;
		CallStart(child);
	}
}

void ComponentInstanceManager::CallPhysicsTick(float elapsed_time, GameObject* game_object) {
	for (auto& component : game_object->GetAllComponents()) {
		if (component == nullptr) continue;
		component->PhysicsTick(elapsed_time);
	}

	for (auto& child : game_object->GetChildren()) {
		if (child == nullptr) continue;
		CallPhysicsTick(elapsed_time, child);
	}
}

void ComponentInstanceManager::CallFrameTick(float elapsed_time, GameObject* game_object) {
	for (auto& component : game_object->GetAllComponents()) {
		if (component == nullptr) continue;
		component->FrameTick(elapsed_time);
	}

	for (auto& child : game_object->GetChildren()) {
		if (child == nullptr) continue;
		CallFrameTick(elapsed_time, child);
	}
}

void ComponentInstanceManager::CallLateTick(float elapsed_time, GameObject* game_object) {
	for (auto& component : game_object->GetAllComponents()) {
		if (component == nullptr) continue;
		component->LateTick(elapsed_time);
	}

	for (auto& child : game_object->GetChildren()) {
		if (child == nullptr) continue;
		CallLateTick(elapsed_time, child);
	}
}