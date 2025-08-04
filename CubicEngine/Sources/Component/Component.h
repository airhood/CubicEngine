#pragma once

#include <vector>
#include "../Object/Object.h"
#include "ComponentInstanceBase.h"

namespace CubicEngine {

	class GameObject;

	class Component abstract : public Object, public ComponentInstanceBase {
	public:
		Component() = default;
		~Component() override = default;

		virtual void Init() {};

		void* Clone_Obj() const override;
		virtual Component* Clone_Comp() const = 0;

		GameObject* RootGameObject();

		int RootSceneNum();
		int CurrentSceneNum();

	private:
		friend class GameObject;
		GameObject* root_game_object;
	};
}