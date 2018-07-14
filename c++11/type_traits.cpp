#include <iostream>
#include <type_traits>
#include <assert.h>

int main () {
    assert(std::is_integral<int>::value);
    assert(std::is_integral<bool>::value);
    assert(std::is_integral<char>::value);

    assert(std::is_floating_point<float>::value);
    assert(!std::is_floating_point<int>::value);

    assert(std::is_void<void>::value);

    std::cout << "main exit!" << std::endl;
}
