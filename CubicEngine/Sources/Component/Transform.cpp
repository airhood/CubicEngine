#include "Transform.h"

using namespace CubicEngine;

void Transform::Init()
{

}

void Transform::Destroy()
{

}

void* Transform::Clone_Obj()
{
    Transform* copy = new Transform();
    copy->position = position;
    copy->rotation = rotation;
    copy->scale = scale;
    return copy;
}

Transform* Transform::Clone()
{
    Transform* copy = new Transform();
    copy->position = position;
    copy->rotation = rotation;
    copy->scale = scale;
    return copy;
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
