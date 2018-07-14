#include <iostream>
#include <vector>

int max(int left, int right) {
    return left > right ? left : right;
}

int ZeroOneBag(const std::vector<int>& wights, const std::vector<int>& values, int bagspace) {
    // 容量为bagspace的背包想放入第i件物品,有两种情况：
    // (1)放入第i件物品
    //      left = totalvalue[i - 1][bagspace - wights[i]] + values[i]
    // (2)不放第i件物品
    //      right = totalvalue[i - 1][bagspace]
    //
    // 容量为bagspace的背包在挑选完i件物品后的总价值：
    // totalvalue[i][bagspace] = max{left, right}
    
    std::vector<std::vector<int>> totalvalue;
    totalvalue.resize(2);
    
    for (int i = 0; i < totalvalue.size(); ++i) {
        totalvalue[i].resize(bagspace + 1, 0);
    }

    for (int i = 1; i < wights.size(); ++i) {
        for (int j = wights[i]; j <= bagspace; ++j) {
            totalvalue[i % 2][j] = max(totalvalue[(i - 1) % 2][j], totalvalue[(i - 1) % 2][j - wights[i]] + values[i]);
        }
    }
    
    for (int i = 1; i < wights.size(); ++i) {
        for (int j = 0; j <= bagspace; ++j) {
            std::cout << totalvalue[i % 2][j] << " ";
        }
        std::cout << std::endl;
    }

    return totalvalue[(wights.size() - 1) % 2][bagspace];
}

int main() {
    std::vector<int> values = {0, 8, 10, 6, 3, 7, 2};
    std::vector<int> wights = {0, 4, 6, 2, 2, 5, 1};
    int bagspace = 12;
    std::cout << ZeroOneBag(wights, values, bagspace) << std::endl;
}
