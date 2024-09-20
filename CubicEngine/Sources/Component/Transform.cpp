#include "Transform.h"

using namespace CubicEngine;

Transform::Transform() {
    _parent = nullptr;
}

void Transform::Destroy()
{

}

void* Transform::Clone_Obj()
{
    Transform* clone = new Transform();
    clone->position = position;
    clone->rotation = rotation;
    clone->scale = scale;
    return clone;
}

Transform* Transform::Clone()
{
    Transform* clone = new Transform();
    clone->position = position;
    clone->rotation = rotation;
    clone->scale = scale;
    return clone;
}

glm::vec3 CubicEngine::Transform::GetWorldPosition()
{
    if (_parent == nullptr) return position;
    return _parent->GetWorldPosition() + position;
}

glm::vec3 CubicEngine::Transform::GetWorldRotation() {
    if (_parent == nullptr) return rotation;
    return _parent->GetWorldRotation() + rotation;
}

glm::vec3 CubicEngine::Transform::GetWorldScale() {
    if (_parent == nullptr) return scale;
    return _parent->GetWorldScale() + scale;
}

void CubicEngine::Transform::SetWorldPosition(glm::vec3 world_position)
{
    position = GetWorldPosition() - world_position;
}

void CubicEngine::Transform::SetWorldRotation(glm::vec3 world_rotation)
{
    rotation = GetWorldRotation() - world_rotation;
}

void CubicEngine::Transform::SetWorldScale(glm::vec3 world_scale)
{
    scale = GetWorldScale() - world_scale;
}

glm::vec3 Transform::front()
{
    glm::vec3 front;
    front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front.y = sin(glm::radians(rotation.x));
    front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    return glm::normalize(front);
}

glm::vec3 Transform::up()
{
    return glm::normalize(glm::cross(front(), world_up));
}

glm::vec3 Transform::right()
{
    return glm::normalize(glm::cross(right(), front()));
}

std::string Transform::ToString() {
    return "position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + "), "
        + "rotation: (" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::to_string(position.z) + "), "
        + "scale: (" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) + ")";
}