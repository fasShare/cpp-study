#include <map>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

int max(int left, int right) {
    return left >= right ? left : right;
}

int main() {
    int n = 0;

    cin >> n;

    vector<int> nums;
    set<int> setnums;
    nums.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        setnums.insert(nums[i]);
    }

    //std::cout << "setnums = " << setnums.size() << std::endl;

    int allmax = 0;
    for (set<int>::iterator iter = setnums.begin(); iter != setnums.end(); ++iter) {
        long count = 0, maxcount = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] >= *iter) {
                count += *iter;
                maxcount = max(maxcount, count);
            } else {
                maxcount = max(maxcount, count);
                count = 0;
            }
        }
        allmax = max(allmax, maxcount);
    }

    std::cout << allmax << std::endl;

    return 0;
}
