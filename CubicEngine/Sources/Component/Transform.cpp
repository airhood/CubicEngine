#include "Transform.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

using namespace CubicEngine;

Transform::Transform() {
    _parent = nullptr;
}

void Transform::Destroy() {

}

Component* Transform::Clone_Comp() const {
    return Clone();
}

void* Transform::Clone_Obj() const {
    return Clone();
}

Transform* Transform::Clone() const {
    Transform* clone = new Transform();
    clone->position = this->position;
    clone->rotation = this->rotation;
    clone->scale = this->scale;
    return clone;
}

glm::vec3 Transform::GetWorldPosition() {
    if (_parent == nullptr) return position;
    return _parent->GetWorldPosition() + position;
}

glm::vec3 Transform::GetWorldRotation() {
    if (_parent == nullptr) return rotation;
    return _parent->GetWorldRotation() + rotation;
}

glm::vec3 Transform::GetWorldScale() {
    if (_parent == nullptr) return scale;
    return _parent->GetWorldScale() + scale;
}

void Transform::SetWorldPosition(glm::vec3 world_position) {
    position = GetWorldPosition() - world_position;
}

void Transform::SetWorldRotation(glm::vec3 world_rotation) {
    rotation = GetWorldRotation() - world_rotation;
}

void Transform::SetWorldScale(glm::vec3 world_scale) {
    scale = GetWorldScale() - world_scale;
}

glm::mat4 Transform::RotationMatrix() const {
    float pitch = glm::radians(rotation.x); // pitch
    float yaw = glm::radians(rotation.y); // yaw
    float roll = glm::radians(rotation.z); // roll

    float cy = cos(yaw);
    float sy = sin(yaw);
    float cp = cos(pitch);
    float sp = sin(pitch);
    float cr = cos(roll);
    float sr = sin(roll);

    glm::mat4 rot;

    rot[0][0] = cy * cr + sy * sp * sr;
    rot[0][1] = sr * cp;
    rot[0][2] = -sy * cr + cy * sp * sr;
    rot[0][3] = 0.0f;

    rot[1][0] = -cy * sr + sy * sp * cr;
    rot[1][1] = cr * cp;
    rot[1][2] = sr * sy + cy * sp * cr;
    rot[1][3] = 0.0f;

    rot[2][0] = sy * cp;
    rot[2][1] = -sp;
    rot[2][2] = cy * cp;
    rot[2][3] = 0.0f;

    rot[3][0] = 0.0f;
    rot[3][1] = 0.0f;
    rot[3][2] = 0.0f;
    rot[3][3] = 1.0f;

    return rot;
}

glm::vec3 Transform::Forward() const {
    glm::mat4 rot = RotationMatrix();
    return glm::normalize(glm::vec3(rot * glm::vec4(0, 0, 1, 0)));
}

glm::vec3 Transform::Right() const {
    glm::mat4 rot = RotationMatrix();
    return glm::normalize(glm::vec3(rot * glm::vec4(1, 0, 0, 0)));
}

glm::vec3 Transform::Up() const {
    glm::mat4 rot = RotationMatrix();
    return glm::normalize(glm::vec3(rot * glm::vec4(0, 1, 0, 0)));
}

std::string Transform::ToString() {
    return "position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z) + "), "
        + "rotation: (" + std::to_string(rotation.x) + ", " + std::to_string(rotation.y) + ", " + std::to_string(position.z) + "), "
        + "scale: (" + std::to_string(scale.x) + ", " + std::to_string(scale.y) + ", " + std::to_string(scale.z) + ")";
}

glm::mat4 Transform::GetModelMatrix() const {
    // Translate -> Rotate -> Scale
    glm::mat4 model(1.0f);
    model = glm::translate(model, position);
    glm::quat rot_quat = glm::quat(rotation);
    model = model * glm::mat4_cast(rot_quat);
    model = glm::scale(model, scale);
    return model;
}