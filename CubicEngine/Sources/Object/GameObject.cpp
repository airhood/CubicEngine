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

void GameObject::Destroy() {

}

void GameObject::SetName(std::string name) {
	this->name = name;
}

std::string GameObject::GetName() const {
	return name;
}

void CubicEngine::GameObject::SetEnabled(bool state)
{
	isEnabled = state;
}

bool CubicEngine::GameObject::IsEnabled()
{
	return isEnabled;
}

void GameObject::AddTag(const std::string tag) {
	tags.insert(tag);
}

void GameObject::AddTags(std::initializer_list<std::string> tags) {
	this->tags.insert(tags);
}

const std::unordered_set<std::string>& GameObject::GetTags() {
	return tags;
}

void GameObject::RemoveTag(std::string tag) {
	tags.erase(tag);
}

void GameObject::RemoveTags(std::initializer_list<std::string> tags) {
	for (auto& tag : tags) {
		this->tags.erase(tag);
	}
}

void GameObject::ClearTags() {
	tags.clear();
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

void GameObject::SetParent(GameObject* parent) {
	this->parent = parent;
}

GameObject* GameObject::GetParent() {
	return parent;
}

void GameObject::AddChild(GameObject* child) {
	children.push_back(child);
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
		game_instances.push_back(instance);
	}
	return component;
}

void GameObject::AddComponent(Component* component) {
	if (component == nullptr) return;
	components.push_back(component);
	if (component->has_instance) {
		GameInstance* instance = dynamic_cast<GameInstance*>(component);
		game_instances.push_back(instance);
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