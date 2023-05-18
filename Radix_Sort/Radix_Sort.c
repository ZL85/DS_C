#include <stdio.h>

// 获取数组中最大的元素
int getMax(int array[], int n) {
    int max = array[0];
    for (int i = 1; i < n; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

// 使用计数排序对数组按照指定的位数进行排序
void countSort(int array[], int n, int exp) {
    int output[n]; // 存储排序结果的临时数组
    int count[10] = {0}; // 存储计数的数组，初始值为0

    // 计算每个数字的出现次数
    for (int i = 0; i < n; i++) {
        count[(array[i] / exp) % 10]++;
    }

    // 将计数数组转换为累加数组，用于确定每个数字在输出数组中的位置
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组的信息，将元素放入输出数组中
    for (int i = n - 1; i >= 0; i--) {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    // 将排序结果复制回原始数组
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
    }
}

// 基数排序主函数
void radixSort(int array[], int n) {
    // 获取数组中的最大值，以确定需要进行排序的位数
    int max = getMax(array, n);

    // 依次对个位、十位、百位...进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(array, n, exp);
    }
}

// 测试基数排序算法
int main() {
    int array[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    radixSort(array, n);

    printf("\nSorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}
/*
 * 该算法使用了基数排序的思想，通过多次计数排序来实现对整数数组的排序。
 * 在计数排序的每一次迭代中，按照指定位数（个位、十位、百位...）将元素分桶，并根据桶的顺序重新排列元素。
 * 通过多次迭代，可以达到对整个数组的排序目的。
 * 在上述代码中，getMax函数用于获取数组中的最大值，countSort函数用于执行一次计数排序，radixSort函数是基数排序的主函数，它通过多次调用countSort来完成排序。
 * 最后，通过main函数测试了基数排序的功能。
 * */