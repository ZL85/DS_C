#include <stdio.h>

// 交换两个元素的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 在数组中选择一个枢纽元素（一般选择第一个元素），将数组划分为两个部分，小于枢纽元素的放在左边，大于枢纽元素的放在右边
int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // 枢纽元素
    int i = low; // 从数组的左边开始
    int j = high; // 从数组的右边开始

    while (i < j) {
        // 从右边开始，找到一个小于枢纽元素的元素
        while (arr[i] <= pivot && i <= high) {
            i++;
        }

        // 从左边开始，找到一个大于枢纽元素的元素
        while (arr[j] > pivot && j >= low) {
            j--;
        }

        // 如果i<j，则交换arr[i]和arr[j]的值
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // 将枢纽元素放到正确的位置上
    swap(&arr[low], &arr[j]);

    return j; // 返回枢纽元素的位置
}

// 快速排序函数
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // 找到枢纽元素的位置
        int pivotIndex = partition(arr, low, high);

        // 对枢纽元素左边的子数组进行快速排序
        quickSort(arr, low, pivotIndex - 1);

        // 对枢纽元素右边的子数组进行快速排序
        quickSort(arr, pivotIndex + 1, high);
    }
}

// 测试示例
int main() {
    int arr[] = { 9, 5, 1, 3, 10, 8, 2, 7, 6, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
/*
 * 该算法的思想是选择一个枢纽元素（通常选择第一个元素），然后通过不断将数组划分为两个部分，使得左边的元素都小于枢纽元素，右边的元素都大于枢纽元素。
 * 然后对划分后的子数组递归地应用相同的过程，直到子数组的大小为1或0，即已经有序。
 * 在实现过程中，首先定义了一个交换函数swap，用于交换两个元素的值。
 * 然后定义了一个划分函数partition，用于在数组中选择枢纽元素并进行划分操作。
 * 划分操作中，使用两个指针i和j分别从数组的左右两端开始，通过不断移动指针和交换元素的方式，将数组划分为两个部分。
 * 最后，将枢纽元素放到正确的位置上，并返回枢纽元素的位置。
 * 接下来，定义了快速排序函数quickSort，其中通过递归调用划分函数将数组划分为更小的子数组，并对子数组进行排序。
 * 在主函数中，我们定义了一个测试示例数组，并输出原始数组的内容。然后调用快速排序函数对数组进行排序，并输出排序后的结果。
 */