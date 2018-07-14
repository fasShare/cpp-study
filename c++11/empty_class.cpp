#include <iostream>
#include <type_traits>
#include <assert.h>

class empty_class {
};

int main () {
    assert(std::is_empty<empty_class>::value);
    empty_class ec;

    std::cout << "sizeof empty_class object = " << sizeof(ec) << std::endl;
    std::cout << "sizeof empty_class = " << sizeof(empty_class) << std::endl;
}
