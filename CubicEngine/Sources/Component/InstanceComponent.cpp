#include "InstanceComponent.h"

using namespace CubicEngine;

InstanceComponent::InstanceComponent() {

}

InstanceComponent::~InstanceComponent() {

}

Scene* InstanceComponent::RootScene() {
	return CORE->GET(SceneManager)->GetScene(SceneNum());
}

Scene* InstanceComponent::CurrentScene() {
	return CORE->GET(SceneManager)->GetCurrentScene();
}

Scene* InstanceComponent::GetScene(int scene_num) {
	return CORE->GET(SceneManager)->GetScene(scene_num);
}