#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

int64_t Max(int64_t left, int64_t right) {
    return left >= right ? left : right;
}

template <typename T>
std::vector<T> ReadNFromCin(size_t n) {
    std::vector<T> ret;
    if (n == 0) {
        return ret;
    }
    ret.resize(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> ret[i];
    }
    return ret;
}

int64_t Min(int64_t left, int64_t right) {
    return left <= right ? left : right;
}

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

int main() {
    int n = 0;

    cin >> n;

    vector<int64_t> av;
    av.resize(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> av[i];
    }

    int k = 0, d = 0;

    cin >> k >> d;

    vector<vector<int64_t>> max_result, min_result;

    max_result.resize(k + 1);
    min_result.resize(k + 1);

    for (int i = 0; i <= k; ++i) {

        max_result[i].resize(n + 1, 0);
        min_result[i].resize(n + 1, 0);

    }

    // k == 1
    for (int i = 1; i <= n; ++i) {
        max_result[1][i] = min_result[1][i] = av[i];
    }

    for (int i = 2; i <= k; ++i) {
        for (int j = i; j <= n; ++j) {
            int64_t maxtmp = numeric_limits<int64_t>::min();
            int64_t mintmp = numeric_limits<int64_t>::max();
            for (int left = Max(i - 1, j - d); left <= j - 1; left++) {
                maxtmp = Max(maxtmp, Max(av[j] * max_result[i - 1][left], av[j] * min_result[i - 1][left]));
                mintmp = Min(mintmp, Min(av[j] * max_result[i - 1][left], av[j] * min_result[i - 1][left]));
            }
            max_result[i][j] = maxtmp;
            min_result[i][j] = mintmp;
        }
    }

    int64_t result = max_result[k][1];

    for (int st = 1; st <= n; ++st) {
        result = Max(result, max_result[k][st]);
    }

    std::cout << result << std::endl;
    PrintMatrix<int64_t>(max_result);

    return 0;
}
