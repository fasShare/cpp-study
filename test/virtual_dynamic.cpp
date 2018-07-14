#include <iostream>

class Vbase {
public:
    virtual void vfunc1() {
        std::cout << "In Vbase vfunc1." << std::endl;
    }
    virtual void vfunc() {
        std::cout << "In Vbase vfunc." << std::endl;
    }
    void func() {
        std::cout << "In vbase func." << std::endl;
    }
private:
    
};

class child : public Vbase {
public:
    virtual void vfunc() {
        std::cout << "In child vfunc." << std::endl;
    }

    void func() {
        std::cout << "In child func." << std::endl;
    }
private:
    
};

int main (int argc, char **argv) {
    Vbase *pc = new child;

    pc->vfunc();

    pc->func();

    return 0;
}
