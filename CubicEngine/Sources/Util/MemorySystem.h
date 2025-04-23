#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <format>
#include "Logger.h"
#include "../Setting.h"

namespace CubicEngine {
    class MemorySystem {
    public:
        static void* Alloc(size_t size) {
#ifdef _DEBUG
#if MEM_DEBUG == 1
            std::cout << "[Memory] Alloc: Requesting " << size << " bytes.\n";
#endif
#endif
            void* ptr = std::malloc(size);
            if (!ptr) {
                throw std::bad_alloc();
            }
            return ptr;
        }

        static void Free(void* ptr) {
#ifdef _DEBUG
#if MEM_DEBUG == 1
            std::cout << "[Memory] Free: Releasing memory.\n";
#endif
#endif
            std::free(ptr);
        }
    };
}