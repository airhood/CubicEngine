#include "MemorySystem.h"

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