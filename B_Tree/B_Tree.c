#include <stdio.h>
#include <stdlib.h>

// B树的最大度数
#define MAX_DEGREE 5

// B树节点的定义
typedef struct Node {
    int key[MAX_DEGREE - 1];      // 存储关键字的数组
    struct Node* child[MAX_DEGREE];  // 子节点的指针数组
    int count;                   // 当前节点的关键字数量
    int leaf;                    // 是否为叶节点
} Node;

// 创建一个新的B树节点
Node* createNode(int leaf) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->count = 0;
    newNode->leaf = leaf;
    for (int i = 0; i < MAX_DEGREE; i++) {
        newNode->child[i] = NULL;
    }
    return newNode;
}

// 在节点中查找关键字的索引位置
int findKeyIndex(Node* node, int key) {
    int index = 0;
    while (index < node->count && node->key[index] < key) {
        index++;
    }
    return index;
}

// 分割满节点
void splitNode(Node* parentNode, int childIndex, Node* childNode) {
    Node* newNode = createNode(childNode->leaf);
    newNode->count = MAX_DEGREE / 2 - 1;
    for (int i = 0; i < newNode->count; i++) {
        newNode->key[i] = childNode->key[i + MAX_DEGREE / 2];
    }
    if (!childNode->leaf) {
        for (int i = 0; i < MAX_DEGREE / 2; i++) {
            newNode->child[i] = childNode->child[i + MAX_DEGREE / 2];
        }
    }
    childNode->count = MAX_DEGREE / 2 - 1;
    for (int i = parentNode->count; i > childIndex; i--) {
        parentNode->child[i + 1] = parentNode->child[i];
    }
    parentNode->child[childIndex + 1] = newNode;
    for (int i = parentNode->count - 1; i >= childIndex; i--) {
        parentNode->key[i + 1] = parentNode->key[i];
    }
    parentNode->key[childIndex] = childNode->key[MAX_DEGREE / 2 - 1];
    parentNode->count++;
}

// 插入关键字到B树节点
void insertNonFull(Node* node, int key) {
    int i = node->count - 1;
    if (node->leaf) {
        while (i >= 0 && node->key[i] > key) {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = key;
        node->count++;
    } else {
        while (i >= 0 && node->key[i] > key) {
            i--;
        }
        i++;
        if (node->child[i]->count == MAX_DEGREE - 1) {
            splitNode(node, i, node->child[i]);
            if (node->key[i] < key) {
                i++;
            }
        }
        insertNonFull(node->child[i], key);
    }
}

// 插入关键字到B树
Node* insert(Node* root, int key) {
    if (root->count == MAX_DEGREE - 1) {
        Node* newNode = createNode(0);
        newNode->child[0] = root;
        splitNode(newNode, 0, root);
        insertNonFull(newNode, key);
        return newNode;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// 在B树中查找关键字
Node* search(Node* node, int key) {
    int i = 0;
    while (i < node->count && key > node->key[i]) {
        i++;
    }
    if (i < node->count && key == node->key[i]) {
        return node;
    } else if (node->leaf) {
        return NULL;
    } else {
        return search(node->child[i], key);
    }
}

// 打印B树的关键字
void printBTree(Node* node) {
    int i;
    for (i = 0; i < node->count; i++) {
        if (!node->leaf) {
            printBTree(node->child[i]);
        }
        printf("%d ", node->key[i]);
    }
    if (!node->leaf) {
        printBTree(node->child[i]);
    }
}

int main() {
    Node* root = createNode(1);  // 创建根节点
    root = insert(root, 10);    // 插入关键字10
    root = insert(root, 20);    // 插入关键字20
    root = insert(root, 5);     // 插入关键字5
    root = insert(root, 15);    // 插入关键字15
    root = insert(root, 30);    // 插入关键字30

    printf("B-Tree keys: ");
    printBTree(root);   // 打印B树的关键字
    printf("\n");

    int key = 15;
    Node* result = search(root, key);   // 在B树中查找关键字15
    if (result) {
        printf("Key %d exists in the B-Tree.\n", key);
    } else {
        printf("Key %d does not exist in the B-Tree.\n", key);
    }

    return 0;
}
