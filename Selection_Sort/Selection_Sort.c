/*
 * 算法思想：简单选择排序是一种基于比较的排序算法，其思想是从待排序序列中选择最小（或最大）的元素放到已排序序列的末尾，
 * 然后再从剩余未排序元素中选择最小（或最大）的元素放到已排序序列的末尾，以此类推，直到所有元素都排序完成。
 * 具体步骤如下：
 * 从待排序序列中选择最小元素，记为当前轮次的最小值。
 * 将最小值与待排序序列的第一个元素交换位置，即将最小值放到已排序序列的末尾。
 * 缩小待排序序列的范围，将已排序序列的长度加1。
 * 重复执行步骤1到步骤3，直到待排序序列为空。
 * */
#include <stdio.h>

// 函数：交换两个元素的值
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 函数：简单选择排序
void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    // 遍历待排序序列
    for (i = 0; i < n-1; i++) {
        // 寻找当前轮次的最小值的索引
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // 将最小值与当前位置交换
        swap(&arr[min_idx], &arr[i]);
    }
}

// 测试
int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    if (n <= 0) {
        printf("Error: The array to be sorted is empty.\n");
        return 1;
    }

    printf("Original sequence: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    selectionSort(arr, n);

    printf("\nSorted sequence: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
