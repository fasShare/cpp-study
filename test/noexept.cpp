#include <iostream>
#include <exception>

void NoexceptFunc() noexcept {
    throw "Exception";
}

int main() {
    try {
        NoexceptFunc();
    } catch (const char *str) {
        std::cout << "Exception:" << str << std::endl;
    }
    return 0;
}
