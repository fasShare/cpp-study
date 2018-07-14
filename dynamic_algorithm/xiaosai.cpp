#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

int Min(int left, int right) {
    return left < right ? left : right;
}

int Max(int left, int right) {
    return left > right ? left : right;
}

void PrintArray(const std::string& prefix, std::vector<int> &arr) {
    std::cout << prefix ;
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

std::string IntToString(int num) {
    char ch[2];
    ch[0] = ch[1] = 0;
    ch[0] = (char)(num % 10  + (int)('0'));
    std::string result = ch;
    num = num / 10;
    while (num != 0) {
        ch[0] = (char)(num % 10  + (int)('0'));
        result = ch + result;
        num = num / 10;
    }
    return result;
}

bool GetMinTime(std::vector<int>& im, std::vector<int>& imd, int in, std::vector<int> &result, int &totalTime) {
    assert(im.size() == imd.size());   
    // in 不存在
    if (in < 0) {
        return false;
    }
    
    // 出现最优解
    if (in == 0) {
        totalTime = 0;
        return true;
    }
    // 已经求过最优解
    if (result[in] > -1) {
        totalTime = result[in];
        return true;
    }

    // 无最优解
    if (result[in] == -2) {
        return false;
    }

    assert(result[in] == -1);
    bool setResult = false;
    result[in] = -1;
    // 最优解待求
    for (int i = 0; i < im.size(); ++i) {
        // 取im以及imd的值
        bool hasmin = GetMinTime(im, imd, in - im[i], result, totalTime);
        if (hasmin) {
            if (-1 == result[in]) {
                result[in] = imd[i] + totalTime;
            } else {
                result[in] = Min(result[in], imd[i] + totalTime);
            }
            setResult = true;
        }
    }

    if (!setResult) {
        result[in] = -2;
    }

    // fuck this status, 程序出了bug
    assert(result[in] != -1);
    totalTime = result[in];
    return -2 != result[in];
}

std::string Search(std::vector<int>& in, std::vector<int>& im, std::vector<int>& imd, int maxn) {
    std::vector<int> result;
    result.resize(maxn + 1, -1);
    //PrintArray("result:", result);    
    // -1 result的初始状态
    // -2 in[i]结合im以及imd无法求出最优解
    // 其他最优解
    bool isTrue = false;
    int minTotal = -2;
    for (int i = 0; i < in.size(); ++i) {
        int totalTime = -2;
        bool hasmin = GetMinTime(im, imd, in[i], result, totalTime);
        if (hasmin) {
            isTrue = true;
            result[in[i]] = totalTime;
            if (minTotal != -2) {
                minTotal = Min(totalTime, minTotal);
            } else {
                minTotal = totalTime;
            }
        } else {
            result[in[i]] = -2;
        }
    }
    if (!isTrue) {
        return "It is not true!";
    }

    return IntToString(minTotal);
}

int main() {
    int n = 0, m = 0;
    
    std::cin >> n;
    std::vector<int> in;
    int maxn = 0;
    in.resize(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> in[i];
        maxn = Max(maxn, in[i]);
    }
    
    if (maxn == 0) {
        std::cout << "0" << std::endl;
        return 0;
    }

    std::cin >> m;
    std::vector<int> im;
    std::vector<int> imd;
    im.resize(m, 0);
    imd.resize(m, 0);
    for (int i = 0; i < m; ++i) {
        std::cin >> im[i] >> imd[i];
    }
    
    std::cout << Search(in, im, imd, maxn) << std::endl;
}
