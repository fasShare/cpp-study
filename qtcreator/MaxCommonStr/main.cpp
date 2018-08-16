#include <iostream>
#include <vector>
#include <string>

using namespace std;

int max(int left, int right) {
    return left >= right ? left : right;
}

int main() {
    vector<string> input;
    input.resize(2);

    int index = 0;
    while (index < 2 && getline(cin, input[index++]));

    vector<vector<int> > result;

    result.resize(input[0].size() + 1);

    for (int i = 0; i < result.size(); ++i) {
        result[i].resize(input[1].size() + 1, 0);
    }
    int maxlen = 0;
    for (string::size_type i = 0; i < input[0].size(); ++i) {
        for (string::size_type j = 0; j < input[1].size(); ++j) {
            if (input[0][i] == input[1][j]) {
                result[i + 1][j + 1] = result[i][j] + 1;
            } else {
                result[i + 1][j + 1] = 0;
            }
            maxlen = max(result[i + 1][j + 1], maxlen);
        }
    }
/*
    for (int i = 0; i < result.size(); ++i) {
        for (int k = 0; k < result[i].size(); ++k) {
            std::cout << result[i][k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
*/
    std::cout << maxlen << std::endl;

    return 0;
}
