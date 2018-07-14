#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    vector<vector<int> > result;
    result.resize(m + 1);
    for (size_t i = 0; i <result.size(); ++i ) {
        result[i].resize(n + 1, 0);
    }
    // 同学编号从1-n
    // result[m][n] 经过m步从第n个同学到达第一个同学
    result[1][1] = 0;
    result[1][n] = 1;
    result[0][1] = 1;

     // 第j个同学通过i步到第1个同学 = 第j+1(右边同学)通过i-1步到达第一个同学方式数 + 第j-1(左边同学)通过i-1步到达第一个同学方式数
    for (int i = 1; i <= m; ++i) {
        // 如果第1个同学经过j步到达第1个同学  = 第j+1(右边同学)通过i-1步到达第一个同学方式数 + 第n(左边同学)通过i-1步到达第一个同学方式数
        result[i-1][0] = result[i-1][n];
        for (int j = 1; j <= n; ++j) {
            // 对j+1求余，因为当j==n时有
            // result[i][n] = result[i-1][j-1] + result[i-1][1]; 
            result[i][j] = result[i-1][j-1] + result[i-1][(j+1) % n];
        }
    }

    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // 输出第一个同学经过M步，又把花传到自己手里面
    cout << result[m][1] << endl;
}
