#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// 哈希节点的结构
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// 哈希表的结构
typedef struct HashTable {
    Node** table;
} HashTable;

// 创建一个新的哈希节点
Node* createNode(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// 创建一个新的哈希表
HashTable* createHashTable() {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->table = (Node**)malloc(TABLE_SIZE * sizeof(Node*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

// 哈希函数，将键映射到哈希表中的索引
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// 在哈希表中插入一个键值对
void insert(HashTable* table, int key, int value) {
    int index = hashFunction(key);

    // 创建新的哈希节点
    Node* newNode = createNode(key, value);

    // 如果该位置为空，则直接插入
    if (table->table[index] == NULL) {
        table->table[index] = newNode;
    } else {
        // 如果该位置不为空，使用链表法解决冲突
        Node* currentNode = table->table[index];
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

// 在哈希表中查找给定键的值
int get(HashTable* table, int key) {
    int index = hashFunction(key);

    // 查找哈希表中指定索引位置的链表
    Node* currentNode = table->table[index];
    while (currentNode != NULL) {
        if (currentNode->key == key) {
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }

    // 如果未找到键，则返回-1表示未找到
    return -1;
}

// 在哈希表中删除给定键的节点
void removeKey(HashTable* table, int key) {
    int index = hashFunction(key);

    // 查找哈希表中指定索引位置的链表
    Node* currentNode = table->table[index];
    Node* previousNode = NULL;

    // 遍历链表，查找要删除的节点
    while (currentNode != NULL) {
        if (currentNode->key == key) {
            // 找到要删除的节点

            // 如果是链表的第一个节点
            if (previousNode == NULL) {
                table->table[index] = currentNode->next;
            } else {
                previousNode->next = currentNode->next;
            }

            // 释放内存
            free(currentNode);
            return;
        }

        // 更新指针
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
}

// 打印哈希表的内容
void printHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* currentNode = table->table[i];
        while (currentNode != NULL) {
            printf("(%d, %d) ", currentNode->key, currentNode->value);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

// 主函数
int main() {
    // 创建哈希表
    HashTable* table = createHashTable();

    // 插入键值对
    insert(table, 5, 10);
    insert(table, 7, 15);
    insert(table, 15, 25);
    insert(table, 16, 35);

    // 打印哈希表
    printHashTable(table);

    // 查找键的值
    int value = get(table, 7);
    printf("Value for key 7: %d\n", value);

    // 删除键
    removeKey(table, 7);

    // 打印更新后的哈希表
    printHashTable(table);

    // 释放哈希表内存
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* currentNode = table->table[i];
        while (currentNode != NULL) {
            Node* tempNode = currentNode;
            currentNode = currentNode->next;
            free(tempNode);
        }
    }
    free(table->table);
    free(table);

    return 0;
}
