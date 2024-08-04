#pragma once

#include "../Object/Object.h"

namespace CubicEngine {
	class Component : public Object {
	public:
		Component() = default;
		~Component() override = default;

		virtual void Init() = 0;

		bool has_instance = false;
	};
}