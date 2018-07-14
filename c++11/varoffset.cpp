#include <iostream>
#include <cstddef>
#include <type_traits>
#include <assert.h>

#define VALUE_OF_PTR(p)     (*((long*)&p))

class test {
public:
    int a;
    int b;
    char c;
    int d;
};

class vtest {
public:
    virtual void vfunc() {}
    int a;
    int b;
    char c;
    int d;
};

struct tb {
    int a;
    int b;
};

struct tc : tb {
    int c;
};

struct dtb {
    virtual void tbtest() {}
    int a;
    int b;
};

struct dtc : dtb {
    int c;
};

void TestClassVariablePtr() {
    std::cout << offsetof(test, a) << std::endl;
    std::cout << offsetof(test, b) << std::endl;
    std::cout << offsetof(test, c) << std::endl;
    std::cout << offsetof(test, d) << std::endl;

    // 类成员变量的指针都是相对于类起始地址的一个偏移量，这句话对不？
    // 为了验证那句话对不，看下带虚函数的,通过虚函数的结果可以看到是对的。^_^
    int test::*ptr = nullptr;
    assert(std::is_member_object_pointer<decltype(ptr)>::value);
    std::cout << "sizeof ptr = " << sizeof ptr << std::endl;
    
    std::cout << "-----------无继承无虚函数---------" << std::endl;

    ptr = &test::a;
    std::cout << "aptr = " << VALUE_OF_PTR(ptr) << std::endl; // 0
 
    ptr = &test::b; 
    std::cout << "bptr = " << VALUE_OF_PTR(ptr) << std::endl; // 4
    char test::*cptr = &test::c; 
    std::cout << "cptr = " << VALUE_OF_PTR(cptr) << std::endl; // 8
    ptr = &test::d;
    std::cout << "dptr = " << VALUE_OF_PTR(ptr) << std::endl; // 12 ，按4字节对齐
    

    std::cout << "is equal one = " << ptr << std::endl;

    std::cout << "-----------无继承有虚函数---------" << std::endl;
    
    int vtest::*vptr = nullptr;
    vptr = &vtest::a;
    std::cout << "vaptr = " << VALUE_OF_PTR(vptr) << std::endl; // 8 前8个字节用于存储vptr
    vptr = &vtest::b; 
    std::cout << "vbptr = " << VALUE_OF_PTR(vptr) << std::endl; // 12
    char vtest::*vcptr = &vtest::c; 
    std::cout << "vcptr = " << VALUE_OF_PTR(vcptr) << std::endl; // 16
    vptr = &vtest::d;
    std::cout << "vdptr = " << VALUE_OF_PTR(vptr) << std::endl; // 20 ，按4字节对齐

    
    std::cout << "-----------有继承无虚函数---------" << std::endl;
    int tc::*pa = &tc::a;
    int tc::*pb = &tc::b;
    int tc::*pc = &tc::c;
    
    std::cout << "tc::*pa = " << VALUE_OF_PTR(pa) << std::endl; // 0
    std::cout << "tc::*pb = " << VALUE_OF_PTR(pb) << std::endl; // 4
    std::cout << "tc::*pc = " << VALUE_OF_PTR(pc) << std::endl; // 8

    std::cout << "-----------有继承有虚函数---------" << std::endl;
    int dtc::*dpa = &dtc::a;
    int dtc::*dpb = &dtc::b;
    int dtc::*dpc = &dtc::c;
    
    std::cout << "dtc::*dpa = " << VALUE_OF_PTR(dpa) << std::endl; // 8 前8个字节为vptr
    std::cout << "dtc::*dpb = " << VALUE_OF_PTR(dpb) << std::endl; // 12
    std::cout << "dtc::*dpc = " << VALUE_OF_PTR(dpc) << std::endl; // 16
}

int main () {
    TestClassVariablePtr(); // 测试指向成员变量的指针
}
