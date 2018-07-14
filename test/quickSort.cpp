#include <iostream>
// 函数参数传入的坐标区间遵循左闭右开原则
int FindPivot(int *arr, int start, int end) {
    // 把arr[start,end)该区间第一个元素定为待确定位置的枢纽元
    int pivot = arr[start];
    // 防止数组越界
    --end;
    while (start < end) {
        // 由于待确定的位置的元素在最右边，本次我们从最左边开始查找小于枢纽元的元素。
        // 这个while循环结束的条件是我们找到了小于枢纽元的元素，或者枢纽元素就是最小元素end==start，arr[start] = pivot;
        while ((end > start) && (arr[end] > pivot)) --end;
        if (end == start) {
            break;
        } 
        // 如果找到小于枢纽元素的值a
        // 把小于枢纽元素的值a放到枢纽元素的位置，此时arr[start]==a,arr[end]==a
        // arr[end]这个位置空间用于存储下面这个while循环找到的大于枢纽元的值b
        arr[start++] = arr[end];
        // 从右向左查找大于枢纽元的元素
        while ((start < end) && (arr[start] < pivot)) ++start;
        // 如果找到元素a的旧位置依旧没有找到比枢纽元大的元素，end==start，说明a的旧位置可以用来存储枢纽元素，毕竟a旧位置右边的元素都大于a，arr[start] = pivot;
        if (end == start) {
            break;
        }
        // 如果在start==end前找到了大于枢纽元的元素b，则把b存储a元素的旧位置，此时从b的新位置之后所有的元素都大于a。end--用于下次从b左边一个位置开始查找。
        arr[end--] = arr[start];
    }
    arr[start] = pivot;
    return start;
}
void QuickSort(int* arr, int start, int end) {
    if (end > start) {
        int pivot = FindPivot(arr, start, end);
        QuickSort(arr, start, pivot);
        QuickSort(arr, pivot + 1, end);
    }
}

int main() {
    int *arr = new int[16]{2, 5, 8, 1, 2, 1, 1, 0, 3, 5, 6, 7, 8, 9, 1, -1};
    QuickSort(arr, 0, 16);

    for (int i = 0; i < 16; i++) {
        std::cout << arr[i] << std::endl;
    }
}
