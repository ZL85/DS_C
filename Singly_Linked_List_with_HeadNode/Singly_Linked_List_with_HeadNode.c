#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
struct Node {
    int data;           // 数据元素
    struct Node* next;  // 指向下一个节点的指针
};

// 创建一个新节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // 分配内存空间
    newNode->data = data;                                              // 设置数据
    newNode->next = NULL;                                              // 将next指针初始化为NULL
    return newNode;                                                    // 返回新节点
}

// 在链表末尾插入节点
void insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);  // 创建新节点

    // 遍历链表，找到最后一个节点
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // 将新节点插入到最后一个节点的后面
    current->next = newNode;
}

// 在链表的开头插入节点
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);  // 创建新节点

    // 将新节点的next指针指向当前头节点
    newNode->next = *head;

    // 将新节点设置为头节点
    *head = newNode;
}

// 在指定位置插入节点
void insertAtPosition(struct Node* head, int data, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        // 在链表开头插入节点
        insertAtBeginning(&head, data);
        return;
    }

    // 创建新节点
    struct Node* newNode = createNode(data);

    // 遍历链表，找到指定位置的前一个节点
    struct Node* current = head;
    int count = 1;
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }

    // 如果找到了指定位置的前一个节点，则将新节点插入到该位置
    if (current != NULL) {
        newNode->next = current->next;
        current->next = newNode;
    } else {
        printf("Invalid position.\n");
    }
}

// 删除指定位置的节点
void deleteAtPosition(struct Node* head, int position) {
    if (head->next == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    struct Node* temp = head;
    struct Node* prev = NULL;

    if (position == 1) {
        // 删除头节点
        head = temp->next;
        free(temp);
        return;
    }

    // 遍历链表，找到指定位置的节点及其前一个节点
    int count = 1;
    while (temp != NULL && count < position) {
        prev = temp;
        temp = temp->next;
        count++;
    }
    // 如果找到了指定位置的节点，则将其删除
    if (temp != NULL) {
        prev->next = temp->next;
        free(temp);
    } else {
        printf("Invalid position.\n");
    }
}

// 显示链表中的所有节点
void displayList(struct Node* head) {
    if (head->next == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* current = head->next;

    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 主函数
int main() {
// 创建头节点
    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    head->data = -1; // 头节点不存储数据，可以设置为特定值，如-1
    head->next = NULL;

    // 在链表末尾插入节点
    insertAtEnd(head, 1);
    insertAtEnd(head, 2);
    insertAtEnd(head, 3);
    insertAtEnd(head, 4);

    // 在链表开头插入节点
    insertAtBeginning(&head, 0);

    // 在指定位置插入节点
    insertAtPosition(head, 5, 3);

    // 删除指定位置的节点
    deleteAtPosition(head, 2);

    // 显示链表中的节点
    displayList(head);

    // 释放链表节点内存
    struct Node *current = head;
    struct Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

/*
在修改后的代码中，我们引入了一个头节点，其数据元素可以设置为特定值，如-1，或者根据实际需求进行调整。
头节点的作用是方便链表操作的统一处理，可以避免对空链表的特殊处理，并且简化插入和删除操作的实现。
带头节点的单链表在插入和删除操作时，不需要单独处理头节点，而是直接操作头节点之后的节点。
*/