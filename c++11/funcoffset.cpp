#include <iostream>
#include <cstddef>
#include <type_traits>
#include <assert.h>

#define VALUE_OF_PTR(p)       (*((long*)&p))
#define FUNCPTR_OF_PTR(p)     (((long*)&p)[0])
#define OFFSET_OF_PTR(p)      (((long*)&p)[1])

class funcTest {
public:
    void ftest() { }
    static void stest() {}
};

void TestClassFuncPtr() {
    void (funcTest::*pftest)() = &funcTest::ftest;
    // 静态函数并被编译器识别为类相关的，而是普通的函数指针
    void (*pstest)() = &funcTest::stest;
    // 16个字节的, 存储的内容主要有一下两个
    // 一个真想真正的函数地址，类似于C语言的普通函数地址
    // 一个adjustoffset，多数情况下会是0，这个会在多继承的情况下出现值差异，见博客：https://blog.csdn.net/u010154685/article/details/54755449
    std::cout << "sizeof pftest = " << sizeof(pftest) << std::endl; 
    std::cout << "true func ptr = " << FUNCPTR_OF_PTR(pftest) << std::endl;
    std::cout << "adjustoffset ptr = " << OFFSET_OF_PTR(pftest) << std::endl;

    std::cout << "sizeof pstest = " << sizeof(pstest) << std::endl; // 8
    std::cout << "true func ptr = " << FUNCPTR_OF_PTR(pstest) << std::endl;
    std::cout << "adjustoffset ptr = " << OFFSET_OF_PTR(pstest) << std::endl;
}

class baseA {
public:
    virtual void testBaseA() { 
        a = 20;
    }
    baseA() {
        a = 11;
    }

    int a; 
};

class baseB {
public:
    virtual void testBaseB() { 
        b = 30;
    }
    baseB() {
        b = 22;
    }
    long long b;
};

class baseC {
public:
    virtual void testBaseC() { 
        c = 40;
    }
    baseC() {
        c = 33;
    }
    long long c;
};

class derived : public baseA, public baseB, public baseC {
public:
    virtual void testDerived() { std::cout << "Test derived" << std::endl; }
};

typedef void (*void_func_void)();
typedef void (*void_baseA_void)(baseA*);
typedef void (*void_baseB_void)(baseB*);
typedef void (*void_baseC_void)(baseC*);
void TestVirtualFuncPtr() {
    std::cout << "align of char :" << alignof(char) << std::endl;
    std::cout << "align of short :" << alignof(short) << std::endl;
    std::cout << "align of int :" << alignof(int) << std::endl;
    std::cout << "align of long :" << alignof(long) << std::endl;
    std::cout << "align of long long :" << alignof(long long) << std::endl;
    std::cout << "align of float :" << alignof(float) << std::endl;
    std::cout << "align of double :" << alignof(double) << std::endl;    

    std::cout << "-------------------------------------------------" << std::endl;

    // 存在对齐问题，见上面不同类型所要求的对齐字节数。
    void (derived::*testBaseA)() = &derived::testBaseA;         // ptr = 1, offset = 0
    void (derived::*testBaseB)() = &derived::testBaseB;         // ptr = 1, offset = 16
    void (derived::*testBaseC)() = &derived::testBaseC;         // ptr = 1, offset = 32
    void (derived::*testDerived)() = &derived::testDerived;     // ptr = 9, offset = 0

    // ptr之所以取1是为了区别与为0的空指针。
    // ptr使用的时候会有一个减1过程

    std::cout << "derived::*testBaseA ptr = " << FUNCPTR_OF_PTR(testBaseA) << " offset = " << OFFSET_OF_PTR(testBaseA) << std::endl;
    std::cout << "derived::*testBaseB ptr = " << FUNCPTR_OF_PTR(testBaseB) << " offset = " << OFFSET_OF_PTR(testBaseB) << std::endl;
    std::cout << "derived::*testBaseC ptr = " << FUNCPTR_OF_PTR(testBaseC) << " offset = " << OFFSET_OF_PTR(testBaseC) << std::endl;
    std::cout << "derived::*testDerived ptr = " << FUNCPTR_OF_PTR(testDerived) << " offset = " << OFFSET_OF_PTR(testDerived) << std::endl;

    derived d;
    unsigned long* pd = (unsigned long *)&d;
    void_func_void* vptr = (void_func_void*)pd[0];

    //vptr[0](); 
    // void testBaseA 汇编代码
    //_ZN5baseA9testBaseAEv:
    //.LFB1201:
    //    .cfi_startproc
    //    pushq   %rbp
    //    .cfi_def_cfa_offset 16
    //    .cfi_offset 6, -16 
    //    movq    %rsp, %rbp
//    .cfi_def_cfa_register 6
//    movq    %rdi, -8(%rbp)  "x64下其中%rdi、%rsi、%rdx，%rcx、%r8、%r9用作传递函数参数
//                            "分别对应第1个参数、第2个参数直到第6个参数,这一步我们rdi中是个随机值，因为我们没有传递参数
//    movq    -8(%rbp), %rax  "取出对象baseA地址，存入rax，这里baseA对象是非预期的，因此下面无法正确输出A的值
//    movl    $20, 8(%rax)    "把20存储到baseA.a处
//    popq    %rbp
//    .cfi_def_cfa 7, 8
//    ret                     "函数返回
//    .cfi_endproc

    //std::cout << "derived.a = " << d.a << std::endl;
    
    //void_baseA_void* basea_func = (void_baseA_void *)pd[0];
    //basea_func[0](&d);
    //std::cout << "derived.a = " << d.a << std::endl;

    d.testBaseB();

    //void_baseB_void* baseb_func = (void_baseB_void *)pd[1];
    //baseb_func[0]((baseB*)((long *)&d + 8));
    //std::cout << "derived.b = " << d.b << std::endl;
    //
    //void_baseC_void* basec_func = (void_baseC_void *)pd[2];
    //basec_func[0]((baseC *)((long *)&d + 16));
    //std::cout << "derived.c = " << d.c << std::endl;
}

void TestVirtualFuncPtr2() {
    derived d;
    //baseC *pc = &d;
    //pc->testBaseC();

    void (derived::*testBaseC)() = &derived::testBaseC;
    void (derived::*testDerived)() = &derived::testDerived;
    (d.*testBaseC)();
    (d.*testDerived)();
}

int main () {
    //TestClassFuncPtr();     // 没有虚函数时，函数指针与ptr
    //TestVirtualFuncPtr();
    //TestVirtualFuncPtr2();
    //std::cout << sizeof(derived) << std::endl;
    TestClassFuncPtr();
}
