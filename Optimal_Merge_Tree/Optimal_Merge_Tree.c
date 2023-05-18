#include <stdio.h>
#include <limits.h>

#define N 6 // 输入数组的大小

// 计算最佳归并树的代价矩阵
void calculateCost(int input[], int cost[][N]) {
    // 初始化代价矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cost[i][j] = 0;
        }
    }

    // 计算归并代价
    for (int len = 2; len <= N; len++) {
        for (int i = 0; i <= N - len; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;

            // 枚举每个划分点，找到最小的归并代价
            for (int k = i; k < j; k++) {
                int curCost = cost[i][k] + cost[k + 1][j] + input[i] * input[k + 1] * input[j + 1];
                if (curCost < cost[i][j]) {
                    cost[i][j] = curCost;
                }
            }
        }
    }
}

// 输出最佳归并树
void printOptimalMergeTree(int cost[][N]) {
    printf("Optimal Merge Tree:\n");
    int level = 0;

    // 输出最佳归并树的层次结构
    for (int len = N; len >= 2; len--) {
        for (int i = 0; i <= N - len; i++) {
            int j = i + len - 1;

            // 输出当前层次的括号
            for (int k = 0; k < level; k++) {
                printf(" ");
            }

            printf("(%d-%d)", i, j);

            // 输出归并代价
            printf(":%d ", cost[i][j]);
        }

        printf("\n");
        level += 2;
    }
}

// 测试最佳归并树算法
int main() {
    int input[N] = {30, 35, 15, 5, 10, 20};
    int cost[N][N];

    calculateCost(input, cost);
    printOptimalMergeTree(cost);

    return 0;
}
/*
 * 该算法实现了计算最佳归并树的概念。
 * 最佳归并树用于在归并排序中选择最优的归并顺序，以使总的归并代价最小。
 * 在提供的代码中，calculateCost函数用于计算最佳归并树的代价矩阵。
 * 它使用动态规划的思想，逐步计算不同长度的归并操作的代价，并将结果存储在cost二维数组中。
 * printOptimalMergeTree函数用于输出最佳归并树的层次结构和归并代价。
 * 在main函数中，通过提供的示例输入数组进行最佳归并树的测试，并打印结果。
 * */