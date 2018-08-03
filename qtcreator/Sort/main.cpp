#include <iostream>
#include <vector>

void Swap(std::vector<int>& arr, int left, int right) {
    int tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
}

// 输出arr[start，end-1]的局部大根堆
void BuildMaxHeap(std::vector<int>& arr, int start, int end) {
    int mid = (end - start) / 2;
    for (int cur = mid; cur >= 0; --cur) {
        int dcur = cur;
        while (dcur * 2 + 1 + start < end) {
            int left = dcur * 2 + 1 + start;
            int right = dcur * 2 + 2 + start;
            int maxChild = left;

            if (right < end) {
                maxChild = arr[right] > arr[left] ? right : left;
            }

            if (arr[dcur + start] < arr[maxChild]) {
                // 存在堆顶元素的交换，递归的更新其子
                Swap(arr, dcur + start, maxChild);
                dcur = maxChild - start;
            } else {
                // 已经是局部大根堆，直接退出
                break;
            }
        }
    }
}

// 从小到大的堆排序
void HeapSortGreater(std::vector<int>& arr, int start, int end) {
    if (start >= end) {
        return;
    }

    while (start < end) {
        BuildMaxHeap(arr, start, end);
        Swap(arr, start, --end);
    }
}

// 从大到小堆排序
void HeapSortLess(std::vector<int>& arr, int start, int end) {
    if (start >= end) {
        return;
    }
    --end;
    while (start <= end) {
        BuildMaxHeap(arr, start, end);
        Swap(arr, start++, end);
    }
}

// shell排序
void ShellSort(std::vector<int>& arr) {
    int size = arr.size();
    for (int dela = size / 2; dela > 0; dela /= 2) {
        for (int i = dela; i < size; ++i) {
            for (int j = i - dela; j >= 0; j -= dela) {
                if (arr[j] > arr[j + dela]) {
                    Swap(arr, j, j + dela);
                }
            }
        }
    }
}

int main()
{
    std::vector<int> arr = {1, 4, 6, 7, 3, 2, 2, 0, 0, 0, 4, 5, 7, 8, 9};

    HeapSortGreater(arr, 0, arr.size());

    for (size_t index = 0; index < arr.size(); ++index) {
        std::cout << arr[index] << " ";
    }
    std::cout << std::endl;

    HeapSortLess(arr, 0, arr.size());

    for (size_t index = 0; index < arr.size(); ++index) {
        std::cout << arr[index] << " ";
    }
    std::cout << std::endl;

    ShellSort(arr);

    for (size_t index = 0; index < arr.size(); ++index) {
        std::cout << arr[index] << " ";
    }
    std::cout << std::endl;

    return 0;
}
