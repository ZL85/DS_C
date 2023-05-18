/*
顺序表是一种线性数据结构，用于存储一组具有相同数据类型的元素。它在内存中以连续的方式存储元素，每个元素占用相同大小的存储单元，并且在表中的位置由元素的物理地址决定。

顺序表的定义通常包含以下几个要素：
存储空间：顺序表需要预先分配一定大小的连续内存空间来存储元素。
元素类型：确定了存储在顺序表中的元素的数据类型。
最大容量：表示顺序表的最大存储容量，即可以存储的元素个数上限。
当前长度：表示当前顺序表中实际存储的元素个数。

顺序表的基本操作包括以下几种：
初始化：创建一个空的顺序表，设置其最大容量和当前长度为0。
插入：在指定位置插入一个新元素，使得插入位置之后的元素向后移动，当前长度加1。
删除：删除指定位置的元素，使得删除位置之后的元素向前移动，当前长度减1。
获取：获取指定位置的元素的值。
查找：根据元素值查找在顺序表中的位置。
修改：修改指定位置的元素的值。
遍历：依次访问顺序表中的每个元素。
判空：判断顺序表是否为空。
判满：判断顺序表是否已满。
销毁：释放顺序表占用的内存空间。

需要注意的是，顺序表的插入和删除操作在位置靠前的元素会涉及到大量的元素移动，因此在频繁插入和删除操作的情况下，顺序表的效率可能较低。

除了上述基本的顺序表操作之外，你还可以根据实际需要添加其他功能来完善顺序表的实现。以下是一些可补充的功能：
动态扩容：当顺序表已满时，自动增加其容量，以容纳更多元素。可以使用realloc函数重新分配更大的内存空间，并将原有元素复制到新空间中。
元素排序：实现对顺序表中的元素进行排序，例如使用冒泡排序、插入排序、快速排序等算法对元素进行升序或降序排列。
元素唯一性：在插入新元素时，检查是否已经存在相同的元素，避免重复插入。可以在插入操作之前先进行查找操作，判断元素是否已经存在。
元素统计：统计顺序表中某个元素出现的次数，或者统计满足某个条件的元素个数。
批量操作：实现一次性插入多个元素、删除多个元素或修改多个元素的功能，提高操作效率。
多表操作：实现对多个顺序表的合并、交集、差集等操作，根据需要进行表间元素的合并、删除或查找等操作。

这些是一些可以补充的功能，根据实际需求和具体场景，你可以进一步扩展顺序表的功能，以满足特定的需求。
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100  // 顺序表的最大容量

typedef struct {
    int data[MAX_SIZE];  // 存储元素的数组
    int length;          // 当前长度
} SeqList;

// 初始化顺序表
void init(SeqList *list) {
    list->length = 0;  // 将长度置为0，表示空表
}

// 在指定位置插入元素
int insert(SeqList *list, int pos, int value) {
    // 检查插入位置是否合法
    if (pos < 0 || pos > list->length || list->length == MAX_SIZE) {
        return 0;  // 插入失败
    }

    // 将插入位置之后的元素向后移动一位
    for (int i = list->length - 1; i >= pos; i--) {
        list->data[i + 1] = list->data[i];
    }

    // 在插入位置处放置新元素
    list->data[pos] = value;
    list->length++;

    return 1;  // 插入成功
}

// 删除指定位置的元素
int removeAt(SeqList *list, int pos) {
    // 检查删除位置是否合法
    if (pos < 0 || pos >= list->length) {
        return 0;  // 删除失败
    }

    // 将删除位置之后的元素向前移动一位
    for (int i = pos + 1; i < list->length; i++) {
        list->data[i - 1] = list->data[i];
    }

    list->length--;

    return 1;  // 删除成功
}

// 获取指定位置的元素值
int get(SeqList *list, int pos) {
    // 检查位置是否合法
    if (pos < 0 || pos >= list->length) {
        return -1;  // 返回一个无效值表示获取失败
    }

    return list->data[pos];
}

// 根据元素值查找在顺序表中的位置
int find(SeqList *list, int value) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            return i;  // 返回找到的位置
        }
    }

    return -1;  // 返回-1表示未找到
}

// 修改指定位置的元素值
int modify(SeqList *list, int pos, int value) {
    // 检查位置是否合法
    if (pos < 0 || pos >= list->length) {
        return 0;  // 修改失败
    }

    list->data[pos] = value;

    return 1;  // 修改成功
}

// 遍历顺序表中的元素
void traverse(SeqList *list) {
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 判断顺序表是否为空
int isEmpty(SeqList *list) {
    return list->length == 0;
}

// 判断顺序表是否已满
int isFull(SeqList *list) {
    return list->length == MAX_SIZE;
}

// 销毁顺序表，释放内存空间
void destroy(SeqList *list) {
    list->length = 0;
    // 释放内存空间
    free(list);
}

int main() {
    SeqList *list = (SeqList *)malloc(sizeof(SeqList));  // 动态分配内存空间

    init(list);  // 初始化顺序表

    printf("%d\n",isEmpty(list)); // 判断顺序表是否为空

    insert(list, 0, 5);  // 在位置0插入元素5
    insert(list, 1, 8);  // 在位置1插入元素8
    insert(list, 2, 3);  // 在位置2插入元素3

    printf("%d\n",isFull(list)); // 判断顺序表是否为满

    printf("%d\n",get(list,1)); //获取顺序表中第二个元素并输出

    printf("Length: %d\n", list->length);  // 输出顺序表的长度

    printf("Elements: ");
    traverse(list);  // 遍历顺序表的元素

    int pos = find(list, 8);  // 查找元素值为8的位置
    if (pos) {
        printf("Value 8 found at position %d\n", pos);
    } else {
        printf("Value 8 not found\n");
    }

    modify(list, 0, 2);  // 修改位置0的元素为2

    removeAt(list, 1);  // 删除位置1的元素

    printf("Elements after modification and deletion: ");
    traverse(list);

    destroy(list);  // 销毁顺序表，释放内存空间

    return 0;
}
