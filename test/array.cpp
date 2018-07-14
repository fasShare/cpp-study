//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
#include <iostream>
#include <array>
int main()
{
    std::array<int, 4> arrayDemo = { 1,2,3,4 };
    std::cout << "arrayDemo:" << std::endl;
    for (auto itor : arrayDemo)
    {
        std::cout << itor << std::endl;
    }
    int arrayDemoSize = sizeof(arrayDemo);
    std::cout << "arrayDemo size:" << arrayDemoSize << std::endl;
    return 0;
}
