/*************************************************************************
    > File Name: sort.cpp
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

int less(const void *a, const void *b) {
    int left = *((int*)a);
    int right = *((int*)b);
    return left - right;
}

int greater(const void *a, const void *b) {
    int left = *((int*)a);
    int right = *((int*)b);
    return right - left;
}

int main(int argc, char** atgv) {
    std::vector<int> seq = {2, 4, 6, 8, 9, 10, 4, 3, 7, 5, 0};
    std::cout << "原序列:";PrintVector(seq);

    std::qsort(seq.data(), seq.size(), sizeof(int), less);
    std::cout << "从小到大排序后:";PrintVector(seq);
    std::qsort(seq.data(), seq.size(), sizeof(int), greater);
    std::cout << "从大到小排序后:";PrintVector(seq);
    return 0;
}
