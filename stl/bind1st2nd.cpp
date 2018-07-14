/*************************************************************************
    > File Name: bind1st2nd.cpp
    > Author: fas
    > Created Time: 2018年07月14日 星期六 10时16分04秒
 ************************************************************************/

#include <iostream>
#include <functional>
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
    std::vector<int> ilist = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> ret;

    std::transform(ilist.begin(), ilist.end(), std::back_inserter(ret), std::bind1st(std::less<int>(), 6));
    PrintVector(ret);
    ret.clear();
    std::transform(ilist.begin(), ilist.end(), std::back_inserter(ret), std::bind2nd(std::less<int>(), 6));
    PrintVector(ret);

    return 0;
}
