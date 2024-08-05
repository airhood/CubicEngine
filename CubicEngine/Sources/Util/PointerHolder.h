#pragma once

#include <string>
#include <map>

#define glfw_PointerHolder() static_cast<PointerHolder*>(glfwGetWindowUserPointer(CORE->window))

namespace CubicEngine {
	class PointerHolder {
	public:
		template <typename T>
		void RegisterPointer(std::string name, T* ptr);
		template <typename T>
		T* GetPointer(std::string name);

	private:
		std::map<std::string, void*> ptr_list;
	};

	template <typename T>
	void PointerHolder::RegisterPointer(std::string name, T* ptr)
	{
		ptr_list.insert({name, ptr});
	}

	template <typename T>
	T* PointerHolder::GetPointer(std::string name)
	{
		auto it = ptr_list.find(name);
		if (it != ptr_list.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}
}
