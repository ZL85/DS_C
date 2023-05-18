#include <stdio.h>

// 置换-选择排序函数
void transpositionSelectionSort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // 在剩余的未排序部分中找到最小值的索引
        for (int j = i + 1; j < n; j++) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        // 如果最小值不在当前位置，则进行置换
        if (minIndex != i) {
            int temp = array[i];
            array[i] = array[minIndex];
            array[minIndex] = temp;
        }
    }
}

// 测试置换-选择排序算法
int main() {
    int array[] = {9, 5, 7, 1, 3};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    transpositionSelectionSort(array, n);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
/*
 * 该算法实现了置换-选择排序的概念。
 * 在每一次迭代中，选择剩余未排序部分的最小值，并将其与当前位置进行置换。
 * 在提供的代码中，transpositionSelectionSort函数实现了置换-选择排序算法。
 * 它使用两层循环，外层循环控制当前位置，内层循环在剩余的未排序部分中找到最小值的索引。
 * 如果最小值不在当前位置，则进行置换操作。
 * 在main函数中，通过提供的示例数组进行置换-选择排序的测试，并打印结果。
 * */