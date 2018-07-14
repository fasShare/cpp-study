/*************************************************************************
    > File Name: inplace_merge.cpp
    > Author: fas
    > Created Time: 2018年07月14日 星期六 11时20分14秒
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

// 使用inplace_merge实现merge_sort
template <class Iter>
void merge_sort(Iter begin, Iter end) {
    if (std::distance(begin, end) > 1) {
        Iter middle = begin;
        // 迭代器类型不同，时间复杂度不同，
        // （1）对于random access iterator时间复杂度O(1)
        // （2）其他迭代器时间复杂度O(n)
        std::advance(middle, (end - begin) / 2);
        merge_sort(begin, middle);
        merge_sort(middle, end);
        std::inplace_merge(begin, middle, end);
    }
}

int main(int argc, char** atgv) {
    std::vector<int> seq = {2, 3, 5, 9, 1, 0, 2, 3, 4, 8, 1};
    
    merge_sort(seq.begin(), seq.end());

    PrintVector(seq);
    return 0;
}
