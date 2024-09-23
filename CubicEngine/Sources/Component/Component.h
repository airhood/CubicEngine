#pragma once

#include <vector>
#include "../Object/Object.h"

namespace CubicEngine {

	class GameObject;

	class GameInstance;

	class Component : public Object {
	public:
		Component() = default;
		~Component() override = default;

		int SceneNum();
		GameObject* RootGameObject();
		
		int AddGameInstance(GameInstance* game_instance);
		std::vector<GameInstance*> GetGameInstances();
		GameInstance* GetGameInstance(int instance_num);
		int InstanceCount();

	private:
		int scene_num;
		friend class GameObject;
		GameObject* root_game_object;

	private:
		std::vector<GameInstance*> game_instances;
	};
}