/*************************************************************************
    > File Name: max.cpp
    > Author: fas
    > Created Time: 2018年07月14日 星期六 13时05分22秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
void PrintVector(const std::vector<T>& vec) {
    for (const auto &val:vec) {
        std::cout << val << " ";
    }   
    std::cout << std::endl;
}

int main(int argc, char** atgv) {
    std::vector<int> seq = {2, 4, 6, 8, 9, 10, 4, 3, 7, 5, 0};
    std::cout << "原序列:";PrintVector(seq);
    std::cout << "max_element 返回最大元素:" << *max_element(seq.begin(), seq.end()) << std::endl;
    std::cout << "max_element + less 返回最大元素:" << *max_element(seq.begin(), seq.end(), std::less<int>()) << std::endl;
    std::cout << "max_element + greater 返回最大元素:" << *max_element(seq.begin(), seq.end(), std::greater<int>()) << std::endl;
    return 0;
}
