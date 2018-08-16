#include <iostream>
#include <vector>

const uint32_t Kface = 6;

// 在一行里面空格分隔打印数组
template<class T>
void PrintVector(const std::vector<T>& vec) {
    for (const auto &val:vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// 在多行里面空格分隔打印矩阵
template<class T>
void PrintMatrix(const std::vector<std::vector<T>>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        PrintVector(vec[i]);
    }
    std::cout << std::endl;
}

std::vector<uint64_t> NumberBuildByDice(size_t n) {
    std::vector<uint64_t> ret;
    if (n == 0) {
        return ret;
    }

    const uint32_t PointSum = Kface * n;

    std::vector<std::vector<uint64_t>> dp;
    dp.resize(n + 1);
    for (size_t index = 0; index < dp.size(); ++index) {
        dp[index].resize(PointSum + 1, 0);
    }

    for (size_t i = 1; i <= Kface; ++i) { // 一个骰子出先数字[1-Kface]的最多出现一次
        dp[1][i] = 1;
    }

    for (size_t i = 2; i <= n; ++i) {
        for (size_t j = i; j <= i * Kface; ++j) { // 第i个骰子出现的最大数字是 i * Kface
            for (size_t k = 1; k <= Kface && k <= j; ++k) {   // 第i个骨子的六面
                dp[i][j] += dp[i - 1][j - k];
            }
        }
    }

    for (size_t i = n; i <= PointSum; ++i) {
        ret.push_back(dp[n][i]);
    }

    PrintMatrix(dp);

    return ret;
}

int main()
{
    auto ret = NumberBuildByDice(2);

    PrintVector(ret);

    return 0;
}
