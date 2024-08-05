#pragma once

#include "ManagerBase.h"
#include "../Object/Scene.h"

namespace CubicEngine {

	class Scene;

	class SceneManager : public ManagerBase {
	public:
		explicit SceneManager() = default;
		~SceneManager();

	public:
		void Init() override;

		void Exterminate() override;

		void StageScene(Scene* scene);
		void OpenScene(Scene* scene);
		void OpenScene(int scene_num);

		Scene* getCurrentScene();
		int getCurrentSceneNum() { return current_scene_num; }
		Scene* getScene(int scene_num);

	private:
		std::vector<Scene*> scenes;
		int current_scene_num = -1;
	};
}