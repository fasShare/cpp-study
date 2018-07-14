#include <iostream>
#include <string>

const char* test() {
    return std::string("shangxiaofei it!").c_str();
}

int main() {
    auto ptr = test();
    std::cout << (int64_t)ptr << std::endl;

    std::string tmp = "Hello bugs!";

    std::cout << (int64_t)&tmp << std::endl;
}
