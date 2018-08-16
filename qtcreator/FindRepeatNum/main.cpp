#include <iostream>
#include <vector>

void swap(std::vector<uint64_t>& nums, size_t left, size_t right) {
    uint64_t tmp = nums[left];
    nums[left] = nums[right];
    nums[right] = tmp;
}

// 把一个数字放到自己对应的位置上最多交换两次，因此本方法时间复杂度为O(n)，空间复杂度O(1)
// 在一个长度为n的数组里的所有数字都在0到n-1的范围内
int FindFirstRepeatNum(std::vector<uint64_t>& nums) {
    for (size_t index = 0; index < nums.size(); ++index) {
        if (nums[index] == index) {
            continue;
        }
        // 如果index是重复的，肯定存在nums[index] != index
        while (nums[index] != index) {
            size_t new_index = nums[index];
            if (nums[index] == nums[new_index]) { // 找到重复的
                return nums[index];
            } else  {
                swap(nums, index, new_index);
            }
        }
    }
    return -1;
}

int main() {
    std::vector<uint64_t> nums = {6, 3, 1, 0, 2, 5, 3};

    std::cout << FindFirstRepeatNum(nums) << std::endl;

    return 0;
}
