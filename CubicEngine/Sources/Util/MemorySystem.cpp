#include "MemorySystem.h"

void* operator new(size_t size) {
    void* ptr = CubicEngine::MemorySystem::Alloc(size);
#ifdef _DEBUG
#if MEM_DEBUG == 1
    std::cout << "[Memory] operator new: Allocated " << size << " bytes.\n";
#endif
#endif
    return ptr;
}

void operator delete(void* ptr) noexcept {
    CubicEngine::MemorySystem::Free(ptr);
#ifdef _DEBUG
#if MEM_DEBUG == 1
    std::cout << "[Memory] operator delete: Memory released.\n";
#endif
#endif
}