#include <stdio.h>

void shellSort(int arr[], int n) {
    int gap, i, j, temp;

    // 初始化间隔值
    for (gap = n / 2; gap > 0; gap /= 2) {
        // 以间隔值为步长进行插入排序
        for (i = gap; i < n; i++) {
            temp = arr[i];

            // 在已排序的子数组中找到正确位置插入元素
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            arr[j] = temp;
        }
    }
}

int main() {
    int arr[] = {9, 5, 2, 7, 1, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    shellSort(arr, n);

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
