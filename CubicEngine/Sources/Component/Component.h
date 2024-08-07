#pragma once

#include "../Object/Object.h"
#include "../Object/GameObject.h"
#include "../Object/GameInstance.h"

namespace CubicEngine {

	class GameObject;

	class GameInstance;

	class Component : public Object {
	public:
		Component() = default;
		~Component() override = default;

		int SceneNum() { return scene_num; }
		GameObject* RootGameObject() { return root_game_object; }
		
		int AddGameInstance(GameInstance* game_instance) { game_instances.push_back(game_instance); }
		std::vector<GameInstance*> GetGameInstances() { return game_instances; }
		GameInstance* GetGameInstance(int instance_num) { return game_instances[instance_num]; }
		int InstanceCount() { return game_instances.size(); }

	private:
		int scene_num;
		friend class GameObject;
		GameObject* root_game_object;

	private:
		std::vector<GameInstance*> game_instances;
	};
}