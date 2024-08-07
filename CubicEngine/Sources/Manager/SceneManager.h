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

		Scene* GetCurrentScene();
		int GetCurrentSceneNum() { return current_scene_num; }
		Scene* GetScene(int scene_num);

	private:
		std::vector<Scene*> scenes;
		int current_scene_num = -1;
	};
}