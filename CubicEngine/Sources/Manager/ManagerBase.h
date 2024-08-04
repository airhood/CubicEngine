#pragma once

namespace CubicEngine {
    class ManagerBase {
    public:
        ManagerBase() = default;
        virtual ~ManagerBase() = default;

        virtual void Init() {}

        virtual void PhysicsTick(float elapsedTime) {}

        virtual void FrameTick(float elapsedTime) {}

        virtual void LateTick(float elapsedTime) {}

        virtual void Exterminate() = 0;
    };
}