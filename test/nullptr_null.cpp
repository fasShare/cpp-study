#include <iostream>
#include <stdio.h>

//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
class Test {
public:
    void TestWork(int index) {
        std::cout << "TestWork 1" << std::endl;
    }
    void TestWork(int *index) {
        std::cout << "TestWork 2" << std::endl;
    }
};

int main() {
    Test test;
    //test.TestWork(NULL);
    test.TestWork(nullptr);

    return 0;
}
