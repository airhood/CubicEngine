#pragma once

#include "Object.h"

namespace CubicEngine {
	class Component : public Object {
	public:
		Component() {}
		~Component() override = default;

		virtual void Init_() = 0;

		bool has_instance = false;
	};
}