#include <cstddef>   // size_t
#include <iostream>  // std::cout
#include <cstdlib>   // std::malloc, std::free

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

void* operator new(size_t size) {
    void* ptr = CubicEngine::MemorySystem::Alloc(size);
#ifdef _DEBUG
    std::cout << "operator new: Allocated " << size << " bytes.\n";
#endif
    return ptr;
}

void operator delete(void* ptr) noexcept {
    CubicEngine::MemorySystem::Free(ptr);
#ifdef _DEBUG
    std::cout << "operator delete: Memory released.\n";
#endif
}