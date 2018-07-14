#include <iostream> 
#include <vector>

using namespace std;

int searchMaxNum(int length, int lastidx, int idx) {
    if (length == 0) {
        return 0;
    }

    if (idx > length) {
        return 1;
    }

    if (idx == length) {
        // 绳子一节都没截
        if (lastidx == 0) {
            return 0;
        }
        return idx - lastidx;
    }
    
    // 截出的绳段长为idx
    int left = (idx - lastidx) * searchMaxNum(length, idx,  idx + 1);
    // 截出绳段长为idx+1
    int right = searchMaxNum(length, lastidx, idx + 1);
  
    return max(left, right);
}

int CutRope(int length) {
    if (length == 0) {
        return length;
    }
    return searchMaxNum(length, 0, 1);
}

int DpCutRope(int length) {
    if (length == 0) {
        return 0;
    }
    std::vector<int> dp;
    dp.resize(length + 1, 1);
    dp[1] = 0;
    dp[0] = 0;
    for (int i = 2; i <= length; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i] = max(max((i - j) * j, dp[i-j] * j), dp[i]);
        }
    }

    return dp[length];
}

int main () {
    int length = 0;
    cin >> length;
    
    cout << CutRope(length) << endl;
    cout << DpCutRope(length) << endl;
}
