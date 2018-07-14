/*************************************************************************
    > File Name: template_factorial.cpp
    > Author: fas
    > Created Time: 2018年07月13日 星期五 20时45分22秒
 ************************************************************************/

#include<iostream>

template <unsigned int n>
struct factorial {
    const static uint64_t value = n * factorial<n - 1>::value;
};

template <>
struct factorial<0> {
    const static uint64_t value = 1;
};

int main(int argc, char** atgv) {
    std::cout << factorial<6>::value << std::endl;
    return 0;
}
