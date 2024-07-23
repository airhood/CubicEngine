#pragma once

#include "Object.h"
#include "GameObject.h"

namespace CubicEngine {

	class GameObject;

	class Component : public Object {
	public:
		Component() {}
		~Component() override = default;

		virtual void Init() = 0;

		bool has_instance = false;
	};
}