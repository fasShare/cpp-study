#include <iostream>

void print(int& val) {
    std::cout << "int& val = " << val << std::endl;
}

void print(int&& val) {
    std::cout << "int&& val = " << val << std::endl;
}

// 函数重载返回值类型需要一样，不然会出问题
// 值的隐式转换还是比较可怕的
//int print(int& val) {
//    std::cout << "int& val = " << val << std::endl;
//    return val;
//}
//
//int print(int&& val) {
//    std::cout << "int&& val = " << val << std::endl;
//    return val;
//}

void test(int& val) {
    print(std::forward<int>(val));
}

void test(int&& val) {
    print(std::forward<int>(val));
}

int main() {
    int val = 20;
    test(val);
    test(std::move(val));
}
