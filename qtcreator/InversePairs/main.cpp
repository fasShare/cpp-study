#include <iostream>
#include <vector>

// 左闭右开原则
uint64_t BinaryCount(std::vector<int>& nums, std::vector<int>& tmp_arr, size_t start, size_t end) {
    if (end - start <= 1) {
        return 0;
    }
    size_t mid = (start + end) / 2;
    uint64_t left_count = BinaryCount(nums, tmp_arr, start, mid);
    uint64_t right_count = BinaryCount(nums, tmp_arr, mid, end);

    uint64_t count = 0;

    size_t left = start;
    size_t right = mid;
    size_t pos = start;

    while (left < mid && right < end) {
        if (nums[right] < nums[left]) {
            tmp_arr[pos++] = nums[right++];
            count += mid - left; // 最好画图来说
        } else {
            tmp_arr[pos++] = nums[left++];
        }
    }

    while (left < mid) {
        tmp_arr[pos++] = nums[left++];
    }

    while (right < end) {
        tmp_arr[pos++] = nums[right++];
    }

    std::copy(tmp_arr.begin() + start, tmp_arr.begin() + end, nums.begin() + start);

    return left_count + right_count + count;
}

uint64_t InversePairs(std::vector<int>& nums) {
    std::vector<int> tmp_arr;
    tmp_arr.resize(nums.size());
    return BinaryCount(nums, tmp_arr, 0, nums.size());
}

int main()
{
    std::vector<int> nums;
    std::cout << InversePairs(nums) << std::endl;
    return 0;
}
