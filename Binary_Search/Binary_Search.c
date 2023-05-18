#include <stdio.h>

// 二分查找函数
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2; // 计算中间元素的索引

        // 检查中间元素是否等于目标值
        if (arr[mid] == target) {
            return mid; // 找到目标值，返回索引
        }

        // 如果中间元素大于目标值，缩小搜索范围到左半部分
        if (arr[mid] > target) {
            right = mid - 1;
        }
        // 如果中间元素小于目标值，缩小搜索范围到右半部分
        else {
            left = mid + 1;
        }
    }

    return -1; // 目标值不存在于数组中
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 12;
    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1) {
        printf("Target value %d does not exist in the array.\n", target);
    } else {
        printf("Target value %d found at index %d.\n", target, result);
    }

    return 0;
}
