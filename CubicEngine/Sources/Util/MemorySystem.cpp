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

void* operator new[](size_t size) {
    void* ptr = CubicEngine::MemorySystem::Alloc(size);
#ifdef _DEBUG
#if MEM_DEBUG == 1
    std::cout << "[Memory] operator new: Allocated " << size << " bytes.\n";
#endif
#endif
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    CubicEngine::MemorySystem::Free(ptr);
#ifdef _DEBUG
#if MEM_DEBUG == 1
    std::cout << "[Memory] operator delete: Memory released.\n";
#endif
#endif
}

void* CubicEngine::MemorySystem::Alloc(size_t size) {
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

void CubicEngine::MemorySystem::Free(void* ptr) {
#ifdef _DEBUG
#if MEM_DEBUG == 1
    std::cout << "[Memory] Free: Releasing memory.\n";
#endif
#endif
    std::free(ptr);
}