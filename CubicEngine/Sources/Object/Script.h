#pragma once

#include "Scene.h"
#include "GameInstance.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {
	
	class Scene;

	class Script : public GameInstance {
	public:

		Scene* RootScene();
		Scene* CurrentScene();
		Scene* GetScene(int scene_num);
	};
}