#include "SceneManager.h"

using namespace CubicEngine;

SceneManager::~SceneManager() {

}

void SceneManager::Init() {

}

void SceneManager::Exterminate() {

}

void CubicEngine::SceneManager::StageScene(Scene* scene) {
	scenes.push_back(scene);
}

void SceneManager::OpenScene(Scene* scene) {
	StageScene(scene);
	current_scene_num = scenes.size() - 1;
}

void SceneManager::OpenScene(int scene_num) {
	if (scenes.size() > scene_num) {
		OpenScene(scenes[scene_num]);
	}
}

Scene* SceneManager::getCurrentScene() {
	if (current_scene_num > -1) {
		if (scenes.size() > current_scene_num) {
			return scenes[current_scene_num];
		}
	}
	return nullptr;
}

Scene* SceneManager::getScene(int scene_num) {
	if (scenes.size() > scene_num) {
		return scenes[scene_num];
	}
	return nullptr;
}