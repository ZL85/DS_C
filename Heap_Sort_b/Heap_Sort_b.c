#include <stdio.h>

// 交换数组中两个元素的位置
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 将指定位置的元素进行堆化
void heapify(int arr[], int n, int i) {
    int largest = i;    // 初始化最大元素为当前位置
    int left = 2 * i + 1;    // 左子节点的位置
    int right = 2 * i + 2;   // 右子节点的位置

    // 如果左子节点大于根节点，更新最大元素位置
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点大于根节点，更新最大元素位置
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大元素不是根节点，则交换根节点与最大元素的位置
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // 对交换后的子树进行堆化
        heapify(arr, n, largest);
    }
}

// 堆排序算法
void heapSort(int arr[], int n) {
    // 构建大根堆，从最后一个非叶子节点开始进行堆化
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 依次取出堆顶元素（最大元素），并进行堆调整
    for (int i = n - 1; i > 0; i--) {
        // 将堆顶元素（最大元素）与当前未排序部分的最后一个元素交换
        swap(&arr[0], &arr[i]);

        // 对剩余的元素重新进行堆化
        heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
/*
 * 该算法的思想是使用大根堆数据结构来进行排序。首先，通过heapify函数将给定的数组堆化，构建大根堆。
 * 堆化过程是从最后一个非叶子节点开始，依次向上对每个子树进行堆化操作。
 * 然后，每次将堆顶元素（最大元素）与当前未排序部分的最后一个元素交换，再对剩余的元素重新进行堆化，即可得到一个有序序列。
 * 重复这个过程，直到整个数组排序完成。
 * 在给定的示例代码中，输入的原始数组为 {12, 11, 13, 5, 6, 7}。
 * 首先，对该数组进行堆排序，得到排序后的数组 {5, 6, 7, 11, 12, 13}。
 * 输出结果为 "Original array: 12 11 13 5 6 7" 和 "Sorted array: 5 6 7 11 12 13"。
 */