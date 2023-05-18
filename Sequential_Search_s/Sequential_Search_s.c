//一般线性表的顺序查找算法
#include <stdio.h>

// 定义线性表元素的类型
typedef int ElementType;

// 定义线性表结构体
typedef struct {
    ElementType data[100]; // 存储线性表元素的数组
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

    return 0;
}
/*
这段代码中，SeqList 是线性表的结构体，包含一个存储线性表元素的数组 data 和线性表的长度 length。
SeqSearch 是顺序查找函数，通过遍历线性表的元素来查找目标元素，找到则返回其索引位置，未找到则返回 -1。
在 main 函数中，首先初始化一个线性表，并读取用户输入的目标元素。然后调用 SeqSearch 函数进行顺序查找，并根据返回值输出查找结果。
请注意，这段代码假定线性表中的元素类型为整数（int）。
如果需要使用其他类型的元素，可以修改 ElementType 的定义，并相应地调整代码中的类型相关部分。
*/
