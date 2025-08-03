#pragma once

#include "../../Object/Object.h"

namespace CubicEngine {
	class Asset : public Object {
	public:
		virtual void* Clone_Obj() = 0;

		std::string path;
	};
}