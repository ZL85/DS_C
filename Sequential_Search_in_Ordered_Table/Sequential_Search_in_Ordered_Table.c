//有序表的顺序查找算法
#include <stdio.h>

// 有序表的顺序查找函数
int sequentialSearch(int arr[], int n, int key) {
    int i;

    // 依次遍历有序表中的元素
    for (i = 0; i < n; i++) {
        // 当找到目标元素时，返回其索引位置
        if (arr[i] == key) {
            return i;
        }

        // 当遇到大于目标元素的元素时，表示目标元素不存在于有序表中
        if (arr[i] > key) {
            break;
        }
    }

    // 如果遍历完整个有序表仍未找到目标元素，则返回-1表示未找到
    return -1;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int n = sizeof(arr) / sizeof(arr[0]); // 有序表的长度
    int key = 7; // 待查找的元素

    int index = sequentialSearch(arr, n, key); // 调用顺序查找函数

    if (index != -1) {
        printf("Target element %d found at index %d.\n", key, index);
    } else {
        printf("Target element %d not found.\n", key);
    }

    return 0;
}

