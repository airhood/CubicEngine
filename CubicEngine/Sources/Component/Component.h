#pragma once

#include <vector>
#include "../Object/Object.h"

namespace CubicEngine {

	class GameObject;

	class GameInstance;

	class Component abstract : public Object {
	public:
		Component() = default;
		~Component() override = default;

		virtual void Init() {};

		virtual Component* Clone_Comp() = 0;

		int SceneNum();
		GameObject* RootGameObject();

	private:
		int scene_num;
		friend class GameObject;
		GameObject* root_game_object;
	};
}