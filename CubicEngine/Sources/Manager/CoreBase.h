#pragma once

namespace CubicEngine {
    class CoreBase {
    public:
        CoreBase() = default;
        virtual ~CoreBase() = default;

        virtual void Init() = 0;
        virtual void Update(float elapsedTime) {};

        virtual void Exterminate() = 0;
    };
}