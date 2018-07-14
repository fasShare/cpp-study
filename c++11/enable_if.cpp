/*************************************************************************
    > File Name: enable_if.cpp
    > Author: fas
    > Created Time: 2018年07月13日 星期五 21时13分51秒
 ************************************************************************/

#include <iostream>
#include <type_traits>

template <class left, class right>
typename std::enable_if<std::is_same<left, right>::value, left>::type less(left l, right r) {
    return l < r ? l : r;
}

int main(int argc, char** atgv) {
    std::cout << "less = " << less("shang", "xiao") << std::endl;
    std::cout << "less = " << less(20, 30) << std::endl;
    
    // 无法编译通过
    // std::cout << "less = " << less(20, 30.0) << std::endl;
    return 0;
}
