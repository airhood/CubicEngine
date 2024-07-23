#pragma once

#include <string>

namespace CubicEngine {

	class Object {
	public:
		Object();

		virtual ~Object();

		virtual void Destroy();

		std::string GetObjectID() const;

	private:
		std::string objectID;
	};
}