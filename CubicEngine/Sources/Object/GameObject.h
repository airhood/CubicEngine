#pragma once

#include <glm.hpp>
#include <vector>
#include <unordered_set>
#include "Object.h"
#include "../Component/Component.h"
#include "GameInstance.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class GameInstance;

	class GameObject : public Object {
	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, Component* component);
		GameObject(std::string name, std::initializer_list<Component*> components);
		
		void Destroy() override;

		void SetName(std::string name);
		std::string GetName() const;
		void SetEnabled(bool state);
		bool IsEnabled();
		void AddTag(std::string tag);
		void AddTags(std::initializer_list<std::string> tags);
		const std::unordered_set<std::string>& GetTags();
		void RemoveTag(std::string tag);
		void RemoveTags(std::initializer_list<std::string> tags);
		void ClearTags();
		bool CheckTagExists(std::string tag);
		bool CheckTagsExists(std::initializer_list<std::string> tags);

		void SetParent(GameObject* parent);
		GameObject* GetParent();
		void AddChild(GameObject* child);
		GameObject* GetChildByName(std::string name);
		GameObject* GetChildByID(std::string id);
		GameObject* GetChildByTag(std::string tag);
		GameObject* GetChildByTags(std::initializer_list<std::string> tags);
		std::vector<GameObject*> GetChildren();
		std::vector<GameObject*> GetChildrenByName(std::string name);
		std::vector<GameObject*> GetChildrenByTag(std::string tag);
		std::vector<GameObject*> GetChildrenByTags(std::initializer_list<std::string> tags);

		template <typename T>
		T* AddComponent();
		void AddComponent(Component* component);
		template <typename T>
		T* GetComponent();

	private:
		std::string name;
		bool isEnabled = true;
		std::unordered_set<std::string> tags;

		GameObject* parent = nullptr;
		std::vector<GameObject*> children;

		std::vector<Component*> components;
	};
}