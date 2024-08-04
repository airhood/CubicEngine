#pragma once

#include <string>

namespace CubicEngine {

	class Object {
	public:
		Object();

		virtual ~Object() = default;

		virtual void Destroy() {}

		virtual void* Clone_Obj() { return nullptr; }

		std::string GetObjectID() const;

	private:
		std::string objectID;
	};
}