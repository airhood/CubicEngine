#pragma once

namespace CubicEngine {

	class ComponentInstanceBase abstract {
	public:
		// game loop
		virtual void Start() {}

		virtual void PhysicsTick(float elapsedTime) {}

		virtual void FrameTick(float elapsedTime) {}

		virtual void LateTick(float elapsedTime) {}

		virtual void OnDestroy() {}
	};
}