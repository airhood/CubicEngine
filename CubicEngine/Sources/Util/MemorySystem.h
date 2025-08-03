#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <format>
#include "Logger.h"
#include "../Setting.h"

namespace CubicEngine {
    class MemorySystem {
    public:
        static void* Alloc(size_t size);

        static void Free(void* ptr);

    private:
        
    };
}