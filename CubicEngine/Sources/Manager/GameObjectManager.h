#pragma once

#include "ManagerBase.h"
#include "../Object/GameObject.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class GameObjectManager : public ManagerBase {
	public:
		explicit GameObjectManager() = default;
		~GameObjectManager();

	public:
		void Init() override;

		void Exterminate() override;

	public:
		void AddGameObject(int scene_num, GameObject* game_object);
		GameObject* GetGameObjectByName(int scene_num, std::string name);
		GameObject* GetGameObjectByID(int scene_num, std::string id);
		GameObject* GetGameObjectByTag(int scene_num, std::string tag);
		GameObject* GetGameObjectByTags(int scene_num, std::initializer_list<std::string> tags);
		std::vector<GameObject*> GetGameObjectsByName(int scene_num, std::string name);
		std::vector<GameObject*> GetGameObjectsByTag(int scene_num, std::string tag);
		std::vector<GameObject*> GetGameObjectsByTags(int scene_num, std::initializer_list<std::string> tags);
	};
}