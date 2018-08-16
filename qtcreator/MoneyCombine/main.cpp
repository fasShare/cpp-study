#include <map>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> nums = {1, 5, 10, 20, 50, 100};
    map<int, int> com = {
        {1, 1},
        {5, 2},
        {10, 4},
    };
    int n = 0;
    cin >> n;
    vector<long> result;
    result.resize(n + 1, 1);
    result[1] = 1;
    for (int i = 1; i <= n; ++i) {
        int nr = 1;
        if (i - 100 > 0) {
            nr = 100;
            result[i] = result[nr] * result[i - nr];
        } else if (i - 50 > 0) {
            nr = 50;
            result[i] = result[nr] * result[i - nr];
        } else if (i - 20 > 0) {
            nr = 20;
            result[i] = result[nr] * result[i - nr];
        } else if (i - 10 >= 0) {
            nr  =10;
            result[i] = com[nr] * result[i - nr];
        } else if (i - 5 >= 0) {
            nr = 5;
            result[i] = com[nr] * result[i - nr];
        }  else {
            result[i] = result[i - nr];
        }

    }
    //for (int i = 0; i <= n; ++i) {
        std::cout << result[n] << std::endl;
    //}

    return 0;
}
