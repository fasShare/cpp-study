/*************************************************************************
    > File Name: dynamicArgs.cpp
    > Author: fas
    > Created Time: 2018年07月13日 星期五 19时57分49秒
 ************************************************************************/

#include <iostream>
#include <string>

template <class T, class SplitType>
void print(SplitType splitchar, T lastone) {
    std::cout << lastone << std::endl;
}

template <class T, class SplitType, class... da>
void print(SplitType splitchar, T next, da... args) {
    std::cout << next << splitchar;
    print(splitchar, args...);
}

template <class SplitType, class... da>
void PrintLine(SplitType splitchar, da... args) {
    if(sizeof...(args) == 0) {
        return;
    }
    print(splitchar, args...);
}

int main(int argc, char** atgv) {
    PrintLine(" ", 1, 2, 3, 5, 6, "end"); 
    return 0;
}
