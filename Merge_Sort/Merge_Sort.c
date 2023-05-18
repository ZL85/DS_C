/*
 * 归并排序（Merge Sort）是一种基于分治思想的排序算法。它将待排序的数组分成两个子数组，然后分别对这两个子数组进行排序，最后将排好序的子数组合并成一个有序数组。
 * 算法思想：
 * 如果数组长度为1或者为空，则无需排序，直接返回。
 * 将数组分成两个子数组，分别递归地对这两个子数组进行排序。
 * 将排好序的两个子数组合并成一个有序数组。
 */
#include <stdio.h>

// 合并两个有序数组
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;

    // 依次比较两个子数组的元素，将较小的元素放入原数组
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素放入原数组
    while (i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// 归并排序
void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;  // 数组长度为1或为空，无需排序
    }

    int mid = size / 2;
    int left[mid];
    int right[size - mid];

    // 将数组分成两个子数组
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    // 递归地对两个子数组进行排序
    mergeSort(left, mid);
    mergeSort(right, size - mid);

    // 合并两个有序子数组
    merge(arr, left, mid, right, size - mid);
}

int main() {
    int arr[] = {9, 2, 5, 1, 6, 3, 8, 7, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    mergeSort(arr, size);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
