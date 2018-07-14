#include <iostream>

using namespace std;

class copyTest {
public:
    copyTest() = default;
    // 下面这样声明拷贝构造函数被报错
    copyTest(copyTest tmp) {
        std::cout << "copy ctor!" << std::endl; 
    }
};

int main() {
    copyTest ct1;
    auto ct2 = ct1;
    (void*)&ct2;
}
