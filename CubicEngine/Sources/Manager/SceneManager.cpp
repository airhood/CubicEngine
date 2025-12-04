#include "SceneManager.h"

using namespace CubicEngine;

SceneManager::~SceneManager() {
	Exterminate();
}

void SceneManager::Init() {

}

void SceneManager::Exterminate() {

}

void SceneManager::StageScene(Scene* scene) {
	scene->scene_num = scenes.size(); // scene_num starts from 0
	scenes.push_back(scene);
}

void SceneManager::OpenScene(Scene* scene) {
	StageScene(scene);
	current_scene_num = scene->scene_num;
}

void SceneManager::OpenScene(int scene_num) {
	if (scenes.size() > scene_num) {
		current_scene_num = scene_num;
	}
}

int SceneManager::GetSceneNum(std::string name) {
	for (int i = 0; i < scenes.size(); i++) {
		if (scenes[i]->name == name) return i;
	}
	return -1;
}

Scene* SceneManager::GetCurrentScene() {
	if (current_scene_num > -1) {
		if (scenes.size() > current_scene_num) {
			return scenes[current_scene_num];
		}
	}
	return nullptr;
}

int SceneManager::GetCurrentSceneNum() const {
	return current_scene_num;
}

Scene* SceneManager::GetScene(int scene_num) {
	if (scenes.size() > scene_num) {
		return scenes[scene_num];
	}
	return nullptr;
}