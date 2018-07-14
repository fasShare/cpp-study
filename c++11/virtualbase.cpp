#include <iostream>
#include <cstddef>

class baseA {
public:
    virtual void testBaseA() { 
        a = 20;
        std::cout << "testBaseA" << std::endl;
    }
    baseA() {
        a = 11;
    }

    long long a;
};

class baseB : virtual public baseA {
public:
    virtual void testBaseB() { 
        b = 30;
        std::cout << "testBaseB" << std::endl;
    }
    baseB() {
        b = 22;
    }
    long long b;
};

class baseC : virtual public baseA {
public:
    virtual void testBaseC() { 
        c = 40;
        std::cout << "testBaseC" << std::endl;
    }
    baseC() {
        c = 33;
    }
    long long c;
};

class derived : public baseB, public baseC {
public:
    virtual void testDerived() { std::cout << "Test derived" << std::endl; }
};

void TestVirtualFuncPtr() {
    derived d;
    unsigned long *pd = (unsigned long *)&d;

    for (int i = 0; i < 6; i++) {
        std::cout << pd[i] << std::endl;
    }

    using vfunc = void (*)();

    vfunc* fp = (vfunc*)pd[0];
    for (int i = 0; i < 2; ++i) {
        fp[i]();
    }
}

int main () {
    TestVirtualFuncPtr();
}
