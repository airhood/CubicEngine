#pragma once

#include <string>
#include "Object.h"
#include "GameObject.h"

namespace CubicEngine {
	class Scene : public Object {
	protected:


	public:
		Scene();
		~Scene();

		std::string name;

		GameObject* GetGameObjectByName(std::string name);
		GameObject* GetGameObjectByID(std::string id);
		GameObject* GetGameObjectByTag(std::string tag);
		GameObject* GetGameObjectByTags(std::initializer_list<std::string> tags);
		GameObject* GetGameObjectsByName(std::string name);
		GameObject* GetGameObjectsByTag(std::string tag);
		GameObject* GetGameObjectsByTags(std::initializer_list<std::string> tags);

	private:
		void Init();
		void InitGameObjects();
		void Tick(float elapsedTime);

		std::vector<GameObject*> game_objects;
	};
}