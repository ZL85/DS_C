//冒泡排序是一种简单的排序算法，它的基本思想是通过相邻元素的比较和交换，将最大（或最小）的元素逐渐 "冒泡" 到待排序序列的一端。
#include <stdio.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;

    // 外层循环控制每趟排序的次数
    for (i = 0; i < n - 1; i++) {

        // 内层循环进行相邻元素的比较和交换
        // 每次循环将当前未排序部分的最大元素冒泡到末尾
        for (j = 0; j < n - i - 1; j++) {
            // 如果当前元素大于后一个元素，则进行交换
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    bubbleSort(arr, n);

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
/*
 * 在上面的代码中，bubbleSort 函数接受一个整数数组 arr 和数组长度 n 作为参数，通过冒泡排序算法对数组进行排序。
 * 内部的两层循环用于比较和交换相邻的元素。外层循环控制排序的趟数，每一趟排序将未排序部分的最大元素冒泡到末尾。
 * 内层循环遍历当前未排序部分，如果相邻元素的顺序不正确，则进行交换。
 * 在主函数 main 中，我们创建了一个整数数组 arr，并计算数组长度 n。
 * 然后，我们打印原始数组的内容，并调用 bubbleSort 函数对数组进行排序。最后，我们打印排序后的数组。
 */