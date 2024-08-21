#include "Time.h"

using namespace CubicEngine;

float CubicEngine::Time::initTime = 0.0f;
float CubicEngine::Time::currentPhysicsTime = 0.0f;
float CubicEngine::Time::currentFrameTime = 0.0f;
float CubicEngine::Time::lastPhysicsTime = 0.0f;
float CubicEngine::Time::lastFrameTime = 0.0f;

float Time::time() {
    return glfwGetTime() - initTime;
}

float Time::physicsTime() {
    return currentPhysicsTime;
}

float Time::frameTime() {
    return currentFrameTime;
}

void Time::updatePhysicsTime() {
    lastPhysicsTime = currentPhysicsTime;
    currentPhysicsTime = glfwGetTime();
}

void Time::updateFrameTime() {
    lastFrameTime = currentFrameTime;
    currentFrameTime = glfwGetTime();
}

float Time::deltaPhysicsTime() {
    return currentPhysicsTime - lastPhysicsTime;
}

float Time::deltaFrameTime() {
    return currentFrameTime - lastFrameTime;
}

void CubicEngine::Time::init() {
    initTime = glfwGetTime();
}
