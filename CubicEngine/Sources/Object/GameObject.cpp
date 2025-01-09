#include "GameObject.h";

using namespace CubicEngine;

GameObject::GameObject() {
	this->name = "";
	Transform* transform = new Transform();
	components.push_back(transform);
	this->_transform = transform;
}

GameObject::GameObject(std::string name) {
	this->name = name;
	Transform* transform = new Transform();
	components.push_back(transform);
	this->_transform = transform;
}

GameObject::GameObject(std::string name, Component* component) {
	this->name = name;
	Transform* transform = new Transform();
	components.push_back(transform);
	this->_transform = transform;
	if (component != nullptr) {
		this->components.push_back(component);
	}
}

GameObject::GameObject(std::string name, std::initializer_list<Component*> components) {
	this->name = name;
	Transform* transform = new Transform();
	this->components.push_back(transform);
	this->_transform = transform;
	for (auto component : components) {
		if (component != nullptr) {
			this->components.push_back(component);
		}
	}
}

void GameObject::Destroy() {
	for (auto& component : components) {
		component->Destroy();
		delete component;
	}

	for (auto& child : children) {
		child->Destroy();
		delete child;
	}
}

void* GameObject::Clone_Obj() {
	return Clone();
}

GameObject* GameObject::Clone() {
	GameObject* clone = new GameObject();
	clone->name = this->name;
	clone->isEnabled = this->isEnabled;
	clone->tags = this->tags;
	clone->layer = this->layer;
	for (auto& child : children) {
		clone->children.push_back(child->Clone());
	}
	for (auto& component : components) {
		clone->components.push_back(component->Clone_Comp());
	}
	return clone;
}

int GameObject::GetRootSceneNum() {
	return root_scene_num;
}

void GameObject::SetName(std::string name) {
	this->name = name;
}

std::string GameObject::GetName() const {
	return name;
}

void GameObject::SetEnabled(bool state) {
	isEnabled = state;
}

bool GameObject::IsEnabled() {
	return isEnabled;
}

void GameObject::AddTag(std::string tag) {
	tags.insert(tag);
}

void GameObject::AddTags(std::initializer_list<std::string> tags) {
	this->tags.insert(tags);
}

const std::unordered_set<std::string> GameObject::GetTags() {
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
	if (parent == nullptr) return;
	parent->DeleteChildPtr(this);
	parent->AddChild(this);

}

GameObject* GameObject::GetParent() {
	return parent;
}

void GameObject::AddChild(GameObject* child) {
	if (child == nullptr) return;
	child->parent = this;
	child->transform()->_parent = _transform;
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

void GameObject::AddComponent(Component* component) {
	if (component == nullptr) return;
	components.push_back(component);
}

std::vector<Component*> GameObject::GetAllComponents() {
	return components;
}

int GameObject::RootSceneNum() {
	return root_scene_num;
}

void GameObject::DeleteChildPtr(GameObject* child) {
	if (child == nullptr) return;
	children.erase(remove(children.begin(), children.end(), child));
}
