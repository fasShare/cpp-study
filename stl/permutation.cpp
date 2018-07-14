/*************************************************************************
    > File Name: permutation.cpp
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
    std::vector<int> seq1 = {2, 4, 6, 8, 9, 10, 4, 3, 7, 0, 5};
    if (std::is_permutation(seq1.begin(), seq1.end(), seq.begin())) {
        std::cout << "seq1 is permutation of seq." << std::endl;
    } else {
        std::cout << "seq1 isn't permutation of seq." << std::endl;
    }

    std::vector<int> per_seq = {1, 2, 3};
    while (next_permutation(per_seq.begin(), per_seq.end())) {
        PrintVector(per_seq);
    }

    return 0;
}
