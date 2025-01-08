#include <cstddef>
#include <iostream>
#include <cstdlib>

namespace CubicEngine {
    class MemorySystem {
    public:
        static void* Alloc(size_t size) {
#ifdef _DEBUG
            std::cout << "MemorySystem Alloc: Requesting " << size << " bytes.\n";
#endif
            void* ptr = std::malloc(size);
            if (!ptr) {
                throw std::bad_alloc();
            }
            return ptr;
        }

        static void Free(void* ptr) {
#ifdef _DEBUG
            std::cout << "MemorySystem Free: Releasing memory.\n";

#endif
            std::free(ptr);
        }
    };
}