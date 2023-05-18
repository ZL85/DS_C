#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;   // 存储元素的数组
    int length;  // 当前长度
    int capacity;  // 最大容量
} SeqList;

// 初始化顺序表
void init(SeqList *list, int capacity) {
    list->data = (int *)malloc(capacity * sizeof(int));
    list->length = 0;
    list->capacity = capacity;
}

// 在指定位置插入元素
int insert(SeqList *list, int pos, int value) {
    // 检查插入位置是否合法
    if (pos < 0 || pos > list->length || list->length == list->capacity) {
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

// 判断
int isFull(SeqList *list) {
    return list->length == list->capacity;
}

// 销毁顺序表，释放内存空间
void destroy(SeqList *list) {
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main() {
    int capacity = 10;  // 设置顺序表的初始容量
    SeqList list;
    init(&list, capacity);  // 初始化顺序表

    printf("%d\n",isEmpty(&list)); // 判断顺序表是否为空

    insert(&list, 0, 5);  // 在位置0插入元素5
    insert(&list, 1, 8);  // 在位置1插入元素8
    insert(&list, 2, 3);  // 在位置2插入元素3

    printf("%d\n",isFull(&list)); // 判断顺序表是否为满

    printf("%d\n",get(&list,1)); //获取顺序表中第二个元素并输

    printf("Length: %d\n", list.length);  // 输出顺序表的长度

    printf("Elements: ");
    traverse(&list);  // 遍历顺序表的元素

    int pos = find(&list, 8);  // 查找元素值为8的位置
    if (pos != -1) {
        printf("Value 8 found at position %d\n", pos);
    } else {
        printf("Value 8 not found\n");
    }

    modify(&list, 0, 2);  // 修改位置0的元素为2

    removeAt(&list, 1);  // 删除位置1的元素

    printf("Elements after modification and deletion: ");
    traverse(&list);

    destroy(&list);  // 销毁顺序表，释放内存空间

    return 0;
}
//通过使用动态内存分配，我们可以根据需要动态调整顺序表的容量，避免固定容量的限制，并在程序结束时释放所分配的内存空间。