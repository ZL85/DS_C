#include <stdio.h>

// 直接插入排序函数
void insertionSort(int arr[], int n) {
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = arr[i]; // 选择当前要插入的元素
        j = i - 1;

        /*
         * 移动已排序序列中的元素，直到找到合适的位置插入
         * 比较 key 和已排序元素 arr[j]，如果 arr[j] 大于 key，则将 arr[j] 后移一位
         */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key; // 在合适位置插入 key
    }
}

// 测试代码
int main() {
    int arr[] = {5, 2, 8, 12, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("Original array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    insertionSort(arr, n); // 调用直接插入排序函数

    printf("\nSorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
