#include <iostream>
#include <stack>
#include <vector>
#include <string>

// 把数M转化为N进制数

using namespace std;

int abs(int n) {
    return n < 0 ? -n : n;
}

int main() {
    int M, N;
    cin >> M >> N;
    stack<char> nums;
    vector<char> chars = {'0', '1', '2', '3',
                          '4', '5', '6', '7',
                          '8', '9', 'A', 'B',
                          'C', 'D', 'E', 'F'};
    int dri = abs(M);
    while (dri != 0) {
        nums.push(chars[dri % N]);
        dri /= N;
    }

    if (M < 0) {
        std::cout << "-";
    }

    while(!nums.empty()) {
        std::cout << nums.top();
        nums.pop();
    }
    std::cout << std::endl;
    return 0;
}
