#include <iostream>

void test(int val) {
    std::cout << "int val = " << val << std::endl;
}
void test(int* val) {
    if (val == NULL || val == nullptr) {
        std::cout << "int val = nullptr" << std::endl;
    } else {
        std::cout << "int val = " << val << std::endl;
    }
}

int main() {
//    test(NULL); // 会产生编译错误,歧义,不知道该调用那个函数了.
    test(nullptr);
}
