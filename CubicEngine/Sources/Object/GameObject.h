#pragma once

#include <glm.hpp>
#include <vector>
#include <unordered_set>

#include "Object.h"
#include "../Component/Component.h"
#include "GameInstance.h"
#include "../Core/EngineCore.h"

namespace CubicEngine {

	class Component;

	class GameObject : public Object {
	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, Component* component);
		GameObject(std::string name, std::initializer_list<Component*> components);
		
		void Destroy() override;

		int GetRootSceneNum() { return root_scene_num; }

		void SetName(std::string name) { this->name = name; }
		std::string GetName() const { return name; }
		void SetEnabled(bool state) { isEnabled = state; }
		bool IsEnabled() { return isEnabled; }
		void AddTag(std::string tag) { tags.insert(tag); }
		void AddTags(std::initializer_list<std::string> tags) { this->tags.insert(tags); }
		const std::unordered_set<std::string>& GetTags() { return tags; }
		void RemoveTag(std::string tag) { tags.erase(tag); }
		void RemoveTags(std::initializer_list<std::string> tags);
		void ClearTags() { tags.clear(); }
		bool CheckTagExists(std::string tag);
		bool CheckTagsExists(std::initializer_list<std::string> tags);

		void SetParent(GameObject* parent) { this->parent = parent; }
		GameObject* GetParent() { return parent; }
		void AddChild(GameObject* child) { children.push_back(child); }
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
		friend class Scene;
		int root_scene_num;

	private:
		std::string name;
		bool isEnabled = true;
		std::unordered_set<std::string> tags;

		GameObject* parent = nullptr;
		std::vector<GameObject*> children;

		std::vector<Component*> components;
	};
}