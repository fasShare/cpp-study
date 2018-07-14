#include <iostream>

template <int N, int M>
struct meta_add {
    const static int value = M + N;
};

int main() {
    std::cout << meta_add<200, 100>::value << std::endl;
}
