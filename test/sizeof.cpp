#include <iostream>

int main() {
    int * pr = new int[20];

    std::cout << "sizeof pr = " << sizeof(pr) << std::endl;

    int ar[20];

    std::cout << "sizeof pr = " << sizeof(ar) << std::endl;

    int ar2[sizeof ar];

    std::cout << "sizeof pr = " << sizeof(ar2) << std::endl;

    int num;

    std::cout << "input num:";
    std::cin >> num;

    int ar3[num];

    std::cout << "sizeof pr = " << sizeof(ar3) << std::endl;
}

