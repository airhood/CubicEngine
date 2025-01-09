#pragma once

#include <string>
#include "Object.h"
#include "GameObject.h"

namespace CubicEngine {

	class SceneManager;

	class GameObject;

	class Scene : public Object {
	public:
		Scene();
		~Scene();

	public:
		void Destroy() override;

		void* Clone_Obj() override;
		Scene* Clone();

		void SetName(std::string name);
		std::string GetName();

		void AddGameObject(GameObject* game_object);
		GameObject* GetGameObjectByName(std::string name);
		GameObject* GetGameObjectByID(std::string id);
		GameObject* GetGameObjectByTag(std::string tag);
		GameObject* GetGameObjectByTags(std::initializer_list<std::string> tags);
		std::vector<GameObject*> GetAllGameObjects();
		std::vector<GameObject*> GetGameObjectsByName(std::string name);
		std::vector<GameObject*> GetGameObjectsByTag(std::string tag);
		std::vector<GameObject*> GetGameObjectsByTags(std::initializer_list<std::string> tags);

	private:
		friend class SceneManager;
		int scene_num = -1;

	private:
		std::string name;
		std::vector<GameObject*> game_objects;
	};
}