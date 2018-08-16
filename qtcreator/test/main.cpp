#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

uint64_t getJiecheng(uint64_t n) {
    if (n <= 1) {
        return 1;
    }
    return getJiecheng(n - 1) * n;
}

int factorial(int n){
    int res = 1;
    for(int i = 1;i<=n;i++)
       res *= i;
    return res;
}

vector<int> KthPermutation2(int n,int k){
    vector<int> vec;
    vector<int> res;
    for(int i = 0;i<n;i++)
       vec.push_back(i+1);
    int base = factorial(n-1);
    k--;
    for(int i = 0;i<n-1;i++){
       int divieRes = k/base;
       k = k%base;
       auto num = next(vec.begin(),divieRes);
       res.push_back(*num);
       vec.erase(num);
       base /= (n-i-1);
    }
    res.push_back(vec[0]);
    return res;
}

int main() {
    string str;

    int n, m, k;

    cin >> n >> m >> k;


    for (int i = 0; i < n; ++i) {
        str += 'a';
    }
    for (int i = 0; i < m; ++i) {
        str += 'z';
    }



    return 0;
}
