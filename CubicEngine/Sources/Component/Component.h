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

		virtual void Init() {};

		void Destroy() override;

		void* Clone_Obj() override;
		Component* Clone();

		int SceneNum();
		GameObject* RootGameObject();

	private:
		int scene_num;
		friend class GameObject;
		GameObject* root_game_object;
	};
}