#include "Script.h"

using namespace CubicEngine;

Scene* Script::RootScene() {
	return CORE->GET(SceneManager)->GetScene(SceneNum());
}

Scene* Script::CurrentScene() {
	return CORE->GET(SceneManager)->GetCurrentScene();
}

Scene* Script::GetScene(int scene_num) {
	return CORE->GET(SceneManager)->GetScene(scene_num);
}
