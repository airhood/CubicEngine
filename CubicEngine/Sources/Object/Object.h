#pragma once

#include "../CubicEngine.h"

#include <iostream>
#include <string>

namespace CubicEngine {

	class Object {
	public:
		Object() = default;

		virtual ~Object() = default;

		virtual void Destroy() {}

		virtual void* Clone_Obj() { return nullptr; }

		virtual std::string ToString() { return ""; };

		std::string GetObjectID() const { return objectID; }

	private:
		std::string objectID;
	};
}

inline std::ostream& operator<<(std::ostream& out, const CubicEngine::Object& ref)
{
	out << ref.GetObjectID();

	return out;
}