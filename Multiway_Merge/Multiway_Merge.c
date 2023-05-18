#include <stdio.h>

#define K 4 // 定义多路归并的路数

// 多路平衡归并函数
void multiwayMerge(int input[][K], int output[], int n) {
    int tree[K]; // 败者树，用于选择最小值
    int leaves[K]; // 叶子节点，记录每个输入数组的当前元素
    int minVal, minIndex, i;

    // 初始化叶子节点和败者树
    for (i = 0; i < K; i++) {
        leaves[i] = 0; // 初始时，每个输入数组的指针指向第一个元素
        tree[i] = n; // 初始时，将n作为初始的最小值
    }

    // 从叶子节点中选出最小值并放入输出数组中
    for (i = 0; i < n; i++) {
        // 在败者树中找出最小值所在的叶子节点
        minIndex = tree[0];
        minVal = input[minIndex][leaves[minIndex]];

        // 选择最小值所在的叶子节点
        for (int j = 1; j < K; j++) {
            if (input[j][leaves[j]] < minVal) {
                minIndex = tree[j];
                minVal = input[minIndex][leaves[minIndex]];
            }
        }

        // 将最小值放入输出数组中
        output[i] = minVal;

        // 更新叶子节点和败者树
        leaves[minIndex]++;
        while (minIndex > 0 && input[minIndex][leaves[minIndex]] >= minVal) {
            minIndex = (minIndex + K - 1) / K; // 更新败者树的节点
            tree[minIndex] = leaves[minIndex]; // 更新败者树中的最小值
        }
    }
}

// 测试多路平衡归并与败者树算法
int main() {
    int input[K][K] = {
        {1, 4, 7, 10},
        {2, 5, 8, 11},
        {3, 6, 9, 12},
        {13, 14, 15, 16}
    };
    int output[K * K];
    int n = K * K;

    printf("Input arrays:\n");
    for (int i = 0; i < K; i++) {
        printf("Array %d: ", i + 1);
        for (int j = 0; j < K; j++) {
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }

    multiwayMerge(input, output, n);

    printf("\nMerged array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", output[i]);
    }

    return 0;
}
/*
 * 该算法实现了多路平衡归并和败者树的概念。多路平衡归并用于合并多个已排序的输入数组，而败者树是一种用于选择最小值的数据结构。
 * 在提供的代码中，multiwayMerge函数实现了多路归并算法。它使用了败者树来选择每次归并的最小值。
 * input是包含K个已排序数组的二维数组，output是用于存储归并结果的一维数组，n是输入数组的总元素数。
 * 在函数中，首先初始化叶子节点和败者树。
 * 然后，通过比较叶子节点的值，在败者树中找到最小值所在的叶子节点，并将最小值放入输出数组中。
 * 随着归并的进行，叶子节点和败者树会不断更新以选择下一个最小值。
 * 在main函数中，通过提供的示例输入数组进行多路平衡归并的测试，并打印结果。
 * */