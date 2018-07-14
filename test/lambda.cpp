#include <iostream>

int main () {
    int flag = 99;

    // 以只读方式捕获
    auto add = [&flag] (int a, int b)->double {
        std::cout << "flag=" << flag << " a=" << a << " b=" << b << std::endl;

        flag += 1;
        return a + b;
    };

    std::cout << "add(1, 9)=" << add(1, 9) << std::endl;
    std::cout << "flag=" << flag << std::endl;

    int *pint = nullptr;
    // 以只读方式捕获
    auto intptr_test = [pint]() {
        //pint = new int;
        *pint=10;
    };

    std::cout << "pint" << (uint64_t)pint << " *pint=" << *pint << std::endl;

    return 0;
}
