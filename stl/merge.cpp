/*************************************************************************
    > File Name: merge.cpp
    > Author: fas
    > Created Time: 2018年07月14日 星期六 11时04分17秒
 ************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

template<class T>
void PrintVector(const std::vector<T>& vec) {
    for (const auto &val:vec) {
        std::cout << val << " ";
    }   
    std::cout << std::endl;
}

int main(int argc, char** atgv) {
    std::vector<int> left = {2, 5, 7, 8, 9};
    std::vector<int> right = {1, 2, 7, 9, 10};
    std::vector<int> result;

    // 默认从小到达排序
    std::merge(left.cbegin(), left.cend(),
                right.cbegin(), right.cend(),
                std::back_inserter(result));
    PrintVector(result);
    result.clear();

    // 如果greater返回true，取left中的元素。
    std::merge(left.cbegin(), left.cend(),
                right.cbegin(), right.cend(),
                std::back_inserter(result), std::greater<int>());
    PrintVector(result);
    result.clear();
    return 0;
}
