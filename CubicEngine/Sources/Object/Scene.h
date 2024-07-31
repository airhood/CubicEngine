#pragma once

#include <string>
#include "Object.h"
#include "GameObject.h"

namespace CubicEngine {

	class GameObject;

	class Scene : public Object {
	public:
		Scene();
		~Scene();

	public:
		void Init();
		void InitGameObjects();
		void PhysicsTick(float elapsedTime);
		void FrameTick(float elapsedTime);
		void LateTick(float elapsedTime);

		void AddGameObject(GameObject* game_object);
		GameObject* GetGameObjectByName(std::string name);
		GameObject* GetGameObjectByID(std::string id);
		GameObject* GetGameObjectByTag(std::string tag);
		GameObject* GetGameObjectByTags(std::initializer_list<std::string> tags);
		std::vector<GameObject*> GetGameObjectsByName(std::string name);
		std::vector<GameObject*> GetGameObjectsByTag(std::string tag);
		std::vector<GameObject*> GetGameObjectsByTags(std::initializer_list<std::string> tags);

	private:
		std::string name;
		std::vector<GameObject*> game_objects;
	};
}