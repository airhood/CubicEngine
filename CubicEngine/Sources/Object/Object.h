#pragma once

#include <string>

namespace CubicEngine {

	class Object {
	public:
		Object() = default;

		virtual ~Object() = default;

		virtual void Destroy() {}

		virtual void* Clone_Obj() { return nullptr; }

		std::string GetObjectID() const { return objectID; }

	private:
		std::string objectID;
	};
}