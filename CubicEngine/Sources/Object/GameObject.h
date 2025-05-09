#pragma once

#include <glm.hpp>
#include <vector>
#include <unordered_set>

#include "Object.h"
#include "../Core/EngineCore.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "LayerMask.h"
#include "../Util/Logger.h"
#include "../Component/Renderer.h"

namespace CubicEngine {

	class Component;

	class Transform;

	class GameObject : public Object {
	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, Component* component);
		GameObject(std::string name, std::initializer_list<Component*> components);

		void Destroy() override;

		void* Clone_Obj() override;
		GameObject* Clone();

		int GetRootSceneNum();

		void SetName(std::string name);
		std::string GetName() const;
		void SetEnabled(bool state);
		bool IsEnabled();
		void AddTag(std::string tag);
		void AddTags(std::initializer_list<std::string> tags);
		const std::unordered_set<std::string> GetTags();
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
		template <typename T>
		std::vector<T*> GetComponents();
		std::vector<Component*> GetAllComponents();

		Transform* transform() { return _transform; }

		int RootSceneNum();

	private:
		friend class Scene;
		int root_scene_num;

		friend class GameObject;
		void DeleteChildPtr(GameObject* child);

	private:
		std::string name;
		bool isEnabled = true;
		std::unordered_set<std::string> tags;
		int layer;

		GameObject* parent = nullptr;
		std::vector<GameObject*> children;

		std::vector<Component*> components;
		Transform* _transform;
	};

	class EngineCore;

	template <typename T>
	T* GameObject::AddComponent() {
		if (!std::is_base_of<Component, T>::value) {
			Logger::Log(LogLevel::ERROR, "Cannot add non-component object as a component");
			return nullptr;
		}
		T* component = new T();
		component->root_game_object = this;
		components.push_back(component);

		auto renderer = dynamic_cast<Renderer*>(component);
		if (renderer) {
			Core::EngineCore::getInstance()->GetRenderManagerFUNC()->AddRenderer(renderer);
			std::cout << "renderer: " << renderer << std::endl;
		}

		return component;
	}

	template <typename T>
	T* GameObject::GetComponent() {
		for (auto component : components) {
			if (component == nullptr) continue;
			if (typeid(component) == typeid(T*)) {
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GameObject::GetComponents() {
		for (auto component : components) {
			if (component == nullptr) continue;
			if (typeid(component) == typeid(T*)) {
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}
}