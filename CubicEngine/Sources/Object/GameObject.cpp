#include "GameObject.h"
#include <vector>

using namespace CubicEngine;

GameObject::GameObject() {
	this->name = "";
}

GameObject::GameObject(std::string name) {
	this->name = name;
}

GameObject::GameObject(std::string name, Component* component) {
	this->name = name;
	if (component != nullptr) {
		this->components.push_back(component);
	}
}

GameObject::GameObject(std::string name, std::initializer_list<Component*> components) {
	this->name = name;
	for (auto component : components) {
		if (component != nullptr) {
			this->components.push_back(component);
		}
	}
}

void GameObject::RemoveTags(std::initializer_list<std::string> tags) {
	for (auto& tag : tags) {
		this->tags.erase(tag);
	}
}

bool GameObject::CheckTagExists(std::string tag) {
	if (tags.find(tag) != tags.end()) {
		return true;
	}
	return false;
}

bool GameObject::CheckTagsExists(std::initializer_list<std::string> tag) {
	for (auto& tag : tags) {
		if (this->tags.find(tag) == this->tags.end()) {
			return false;
		}
	}
	return true;
}

GameObject* GameObject::GetChildByName(std::string name) {
	for (auto child : children) {
		if (child->GetName() == name) return child;
	}
	return nullptr;
}

GameObject* GameObject::GetChildByID(std::string id) {
	for (auto child : children) {
		if (child->GetObjectID() == id) return child;
	}
	return nullptr;
}

GameObject* GameObject::GetChildByTag(std::string tag) {
	for (auto child : children) {
		if (child->CheckTagExists(tag)) return child;
	}
	return nullptr;
}

GameObject* GameObject::GetChildByTags(std::initializer_list<std::string> tags) {
	for (auto child : children) {
		if (child->CheckTagsExists(tags)) return child;
	}
	return nullptr;
}

std::vector<GameObject*> GameObject::GetChildren() {
	return children;
}

std::vector<GameObject*> GameObject::GetChildrenByName(std::string name) {
	std::vector<GameObject*> results;
	for (auto& child : children) {
		if (child->GetName() == name) results.push_back(child);
	}
	return results;
}

std::vector<GameObject*> GameObject::GetChildrenByTag(std::string tag) {
	std::vector<GameObject*> results;
	for (auto& child : children) {
		if (child->CheckTagExists(tag)) results.push_back(child);
	}
	return results;
}

std::vector<GameObject*> GameObject::GetChildrenByTags(std::initializer_list<std::string> tags) {
	std::vector<GameObject*> results;
	for (auto& child : children) {
		if (child->CheckTagsExists(tags)) results.push_back(child);
	}
	return results;
}

template <typename T>
T* GameObject::AddComponent() {
	T* component = new T();
	components.push_back(component);
	if (component->has_instance) {
		GameInstance* instance = dynamic_cast<GameInstance*>(component);
		CORE->GET(GameInstanceManager)->AddGameInstance(instance);
	}
	return component;
}

void GameObject::AddComponent(Component* component) {
	if (component == nullptr) return;
	components.push_back(component);
	if (component->has_instance) {
		GameInstance* instance = dynamic_cast<GameInstance*>(component);
		CORE->GET(GameInstanceManager)->AddGameInstance(instance);
	}
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