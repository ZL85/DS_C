/*
单链表（Singly Linked List）是一种常见的线性数据结构，由一系列节点组成，每个节点包含数据元素和一个指向下一个节点的指针。

在单链表中，每个节点包含两个部分：
数据域（Data）：用于存储节点的数据元素。
指针域（Next）：用于指向下一个节点的指针。

单链表的最后一个节点指针域指向空（null），表示链表的结束。
*/
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
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);  // 创建新节点

    // 如果链表为空，将新节点设置为头节点
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // 遍历链表，找到最后一个节点
    struct Node* current = *head;
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
void insertAtPosition(struct Node** head, int data, int position) {
    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        // 在链表开头插入节点
        insertAtBeginning(head, data);
        return;
    }

    // 创建新节点
    struct Node* newNode = createNode(data);

    // 遍历链表，找到指定位置的前一个节点
    struct Node* current = *head;
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
void deleteAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    if (position <= 0) {
        printf("Invalid position.\n");
        return;
    }

    struct Node* temp = *head;

    if (position == 1) {
        // 删除头节点
        *head = temp->next;
        free(temp);
        return;
    }
    // 遍历链表，找到指定位置的前一个节点
    int count = 1;
    struct Node* prev = NULL;
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
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = head;

    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 主函数
int main() {
    struct Node *head = NULL; // 初始化链表为空
    // 在链表末尾插入节点
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);

// 在链表开头插入节点
    insertAtBeginning(&head, 0);

// 在指定位置插入节点
    insertAtPosition(&head, 5, 3);

// 删除指定位置的节点
    deleteAtPosition(&head, 2);

// 显示链表中的节点
    displayList(head);

    return 0;
}

/*
这段代码演示了如何定义一个单链表的结构体以及如何执行插入和删除操作。
主函数中的示例代码创建了一个链表，然后在链表的末尾插入几个节点，
接着在链表的开头插入一个节点，然后在指定位置插入一个节点，
最后删除一个指定位置的节点，并显示最终链表的内容。
*/
