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

void GameObject::Init() {
	InitComponents();
	InitChildren();
}

void GameObject::InitComponents() {
	for (auto component : components) {
		component->Init();
	}
}

void GameObject::InitChildren() {
	for (auto child : children) {
		child->Init();
	}
}

void GameObject::Tick(float elapsedTime) {

}

void GameObject::TickComponentGameInstances(float elapsedTime) {
	for (auto game_instance : game_instances) {
		game_instance->Tick(elapsedTime);
	}
}

void GameObject::TickChildren(float elapsedTime) {
	for (auto child : children) {
		child->Tick(elapsedTime);
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

template <typename T>
T* GameObject::AddComponent() {
	T* component = new T();
	components.push_back(component);
	if (component->has_instance) {
		GameInstance* instance = dynamic_cast<GameInstance*>(component);
		game_instances.push_back(instance);
	}
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
}