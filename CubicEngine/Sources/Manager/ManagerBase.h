#pragma once

namespace CubicEngine {
    class ManagerBase {
    public:
        ManagerBase() = default;
        virtual ~ManagerBase() = default;

        virtual void Init() = 0;
        virtual void PhysicsTick(float elapsedTime) = 0;
        virtual void FrameTick(float elapsedTime) = 0;
        virtual void LateTick(float elapsedTime) = 0;

        virtual void Exterminate() = 0;
    };
}