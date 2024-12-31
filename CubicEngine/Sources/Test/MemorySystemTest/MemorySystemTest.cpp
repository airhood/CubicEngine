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
    // Example ��ü ���� (�޸� �Ҵ�� ������ ȣ��)
    Example* ex = new Example(); // operator new ȣ��, �� ���� Example ������ ȣ��

    // Example ��ü ���� (�Ҹ��� ȣ��� �޸� ����)
    delete ex; // Example �Ҹ��� ȣ��, �� ���� operator delete ȣ��

    return 0;
}