#include "../Util/MemorySystem.h"

using namespace CubicEngine;

class Example {
public:
    Example() {
        std::cout << "Example Constructor: Object created.\n";
    }

    ~Example() {
        std::cout << "Example Destructor: Object destroyed.\n";
    }
};

int main(void)
{
    // Example 객체 생성 (메모리 할당과 생성자 호출)
    Example* ex = new Example(); // operator new 호출, 그 다음 Example 생성자 호출

    // Example 객체 해제 (소멸자 호출과 메모리 해제)
    delete ex; // Example 소멸자 호출, 그 다음 operator delete 호출

    return 0;
}