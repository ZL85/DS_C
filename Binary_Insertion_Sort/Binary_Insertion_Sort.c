#include <stdio.h>

// 折半插入排序函数
void binaryInsertionSort(int arr[], int n) {
    int i, j, key, left, right, mid;

    // 从第二个元素开始，逐个插入到已排序部分
    for (i = 1; i < n; i++) {
        key = arr[i];    // 当前待插入的元素
        left = 0;        // 已排序部分的左边界
        right = i - 1;   // 已排序部分的右边界

        // 使用二分查找找到插入位置
        while (left <= right) {
            mid = (left + right) / 2;    // 已排序部分的中间位置

            // 如果当前元素小于中间位置元素，则在左半部分继续查找
            if (key < arr[mid])
                right = mid - 1;
            // 否则，在右半部分继续查找
            else
                left = mid + 1;
        }

        // 将已排序部分中大于key的元素都向后移动一个位置
        for (j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
        }

        // 将key插入到正确位置
        arr[left] = key;
    }
}

// 测试示例
int main() {
    int arr[] = {5, 2, 8, 4, 6, 1, 3, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    binaryInsertionSort(arr, n);

    printf("\nSorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
