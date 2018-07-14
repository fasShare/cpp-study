#include <iostream>
#include <vector>

int max(int left, int right) {
    return left > right ? left : right;
}

int CompleteBag(const std::vector<int>& wights, const std::vector<int>& values, int bagspace) {
    // 容量为bagspace的背包在放入第i件物品时，可以放入1件，2件 ... k件
    // totalvalue[i][bagspace] = max{totalvalue[i][bagspace - k * wights[i]] + k * values[i], totalvalue[i - 1][bagspace]} 
    // 如果暂时不考虑k的话可以简化为：
    // totalvalue[i][bagspace] = max{totalvalue[i][bagspace - wights[i]] + values[i], totalvalue[i - 1][bagspace]}
    // 和01背包不同的是，完全背包在装物品i时只使用了物品i-1时的一个状态，同理装物品i+1时也会只使用物品i的一个状态，
    // 因此上面的二维方程可以转化为下面的一维方程。
    // totalvalue[bagspace] = max{totalvalue[bagspace - wights[i]] + values[i], totalvalue[bagspace]}
    std::vector<int> totalvalue;
    totalvalue.resize(bagspace + 1, 0);

    for (int i = 1; i < wights.size(); ++i) {
        for (int j = wights[i]; j <= bagspace; ++j) {
            totalvalue[j] = max(totalvalue[j - wights[i]] + values[i], totalvalue[j]);
        }
    }

    return totalvalue[bagspace];
}

int CompleteBagPlus(const std::vector<int>& wights, const std::vector<int>& values, int bagspace) {
    std::vector<int> totalvalue;

}

int main() {
    std::vector<int> values = {0, 5, 4, 3, 2, 1};
    std::vector<int> wights = {0, 1, 2, 3, 4, 5};
    int bagspace = 10;
    std::cout << CompleteBag(wights, values, bagspace) << std::endl;
}
