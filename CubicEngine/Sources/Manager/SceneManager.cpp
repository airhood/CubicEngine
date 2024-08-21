#include "SceneManager.h"

using namespace CubicEngine::Core;

SceneManager::~SceneManager() {

}

void SceneManager::Init() {

}

void SceneManager::Exterminate() {

}

void SceneManager::StageScene(CubicEngine::Scene* scene) {
	scene->scene_num = scenes.size();
	scenes.push_back(scene);
}

void SceneManager::OpenScene(CubicEngine::Scene* scene) {
	StageScene(scene);
	current_scene_num = scenes.size() - 1;
}

void SceneManager::OpenScene(int scene_num) {
	if (scenes.size() > scene_num) {
		OpenScene(scenes[scene_num]);
	}
}

CubicEngine::Scene* SceneManager::GetCurrentScene() {
	if (current_scene_num > -1) {
		if (scenes.size() > current_scene_num) {
			return scenes[current_scene_num];
		}
	}
	return nullptr;
}

CubicEngine::Scene* SceneManager::GetScene(int scene_num) {
	if (scenes.size() > scene_num) {
		return scenes[scene_num];
	}
	return nullptr;
}