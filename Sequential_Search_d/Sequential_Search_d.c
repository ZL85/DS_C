//用动态内存分配实现的一般线性表的顺序查找算法
#include <stdio.h>
#include <stdlib.h>

// 定义线性表元素的类型
typedef int ElementType;

// 定义线性表结构体
typedef struct {
    ElementType *data; // 指向存储线性表元素的数组
    int length; // 线性表的长度
} SeqList;

// 顺序查找函数
int SeqSearch(SeqList list, ElementType target) {
    int i;
    for (i = 0; i < list.length; i++) {
        if (list.data[i] == target) {
            return i; // 找到目标元素，返回索引位置
        }
    }
    return -1; // 未找到目标元素，返回-1
}

int main() {
    SeqList list;
    int i, target, result;

    // 动态分配存储线性表元素的数组内存
    list.data = (ElementType *)malloc(100 * sizeof(ElementType));
    if (list.data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 初始化线性表
    list.length = 5;
    list.data[0] = 2;
    list.data[1] = 5;
    list.data[2] = 8;
    list.data[3] = 10;
    list.data[4] = 13;

    // 输入要查找的目标元素
    printf("Enter the target element: ");
    scanf("%d", &target);

    // 调用顺序查找函数
    result = SeqSearch(list, target);

    // 输出查找结果
    if (result == -1) {
        printf("Target element not found.\n");
    } else {
        printf("Target element found at index %d.\n", result);
    }

    // 释放动态分配的内存
    free(list.data);

    return 0;
}
/*
在这段代码中，使用 malloc 函数动态分配了存储线性表元素的数组内存。
在 malloc 的调用中，通过 100 * sizeof(ElementType) 来指定要分配的内存大小，sizeof(ElementType) 返回元素类型的大小，这里是整数类型 int 的大小。
在程序结束前，使用 free 函数释放了动态分配的内存，以避免内存泄漏。
请注意，动态分配的内存需要在不再使用时手动释放，以防止内存泄漏。
*/