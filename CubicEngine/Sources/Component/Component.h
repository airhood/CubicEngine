#pragma once

#include "../Object/Object.h"

namespace CubicEngine {
	class Component : public Object {
	public:
		Component() = default;
		~Component() override = default;

		bool has_instance = false;
	};
}