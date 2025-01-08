#pragma once

#include <vector>
#include "../Object/Object.h"
#include "ComponentInstanceBase.h"

namespace CubicEngine {

	class GameObject;

	class Component abstract : public Object, ComponentInstanceBase {
	public:
		Component() = default;
		~Component() override = default;

		virtual void Init() {};

		void* Clone_Obj() override;
		virtual Component* Clone_Comp() = 0;

		GameObject* RootGameObject();

		int RootSceneNum();
		int CurrentSceneNum();

	private:
		friend class GameObject;
		GameObject* root_game_object;
	};
}