#include <stdio.h>
#include <stdlib.h>

// 定义B+树节点的最大度数
#define MAX_DEGREE 5

// 定义B+树节点的数据类型
typedef struct Node {
    int keys[MAX_DEGREE - 1];           // 键值数组
    struct Node* children[MAX_DEGREE];  // 子节点指针数组
    struct Node* next;                  // 下一个叶节点指针
    int num_keys;                       // 键值对数量
    int is_leaf;                        // 是否为叶节点
} Node;

// 创建一个新的B+树节点
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->num_keys = 0;
    newNode->is_leaf = 0;
    newNode->next = NULL;
    for (int i = 0; i < MAX_DEGREE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// 在B+树节点中插入键值对
void insertIntoNode(Node* node, int key, Node* child) {
    int i;
    // 找到插入位置
    for (i = node->num_keys - 1; i >= 0 && node->keys[i] > key; i--) {
        node->keys[i + 1] = node->keys[i];
        node->children[i + 2] = node->children[i + 1];
    }
    node->keys[i + 1] = key;
    node->children[i + 2] = child;
    node->num_keys++;
}

// 插入键值对到B+树
Node* insert(Node* root, int key) {
    if (root == NULL) {
        // 树为空，创建根节点并插入键值对
        Node* newNode = createNode();
        newNode->is_leaf = 1;
        newNode->keys[0] = key;
        newNode->num_keys++;
        return newNode;
    }

    Node* currentNode = root;
    Node* parentNode = NULL;

    // 寻找插入位置
    while (!currentNode->is_leaf) {
        int i;
        for (i = 0; i < currentNode->num_keys; i++) {
            if (currentNode->keys[i] > key) {
                break;
            }
        }
        parentNode = currentNode;
        currentNode = currentNode->children[i];
    }

    // 在叶节点中插入键值对
    insertIntoNode(currentNode, key, NULL);

    // 如果当前节点的键值对数量超过最大值，则进行节点分裂
    if (currentNode->num_keys >= MAX_DEGREE - 1) {
        Node* newChild = createNode();
        int mid = currentNode->num_keys / 2;

        // 将后一半的键值对移动到新节点
        for (int i = mid + 1; i < currentNode->num_keys; i++) {
            newChild->keys[i - mid - 1] = currentNode->keys[i];
            newChild->children[i - mid - 1] = currentNode->children[i];
            newChild->num_keys++;
            currentNode->num_keys--;
        }
        newChild->children[newChild->num_keys] = currentNode->children[currentNode->num_keys];

        // 更新父节点的键值对和子节点
        if (parentNode == NULL) {
            parentNode = createNode();
            root = parentNode;
        }
        insertIntoNode(parentNode, currentNode->keys[mid], newChild);
        currentNode->num_keys--;

        // 迭代分裂直到根节点
        while (parentNode->num_keys >= MAX_DEGREE) {
            Node* newParent = createNode();
            mid = parentNode->num_keys / 2;
            newParent->is_leaf = 0;

            for (int i = mid + 1; i < parentNode->num_keys; i++) {
                newParent->keys[i - mid - 1] = parentNode->keys[i];
                newParent->children[i - mid - 1] = parentNode->children[i];
                newParent->num_keys++;
                parentNode->num_keys--;
            }
            newParent->children[newParent->num_keys] = parentNode->children[parentNode->num_keys];
            insertIntoNode(newParent, parentNode->keys[mid], parentNode);
            parentNode->num_keys--;

            parentNode = newParent;
        }
    }

    return root;
}

// 从B+树节点中删除键值对
void deleteFromNode(Node* node, int key) {
    int i = 0;
    while (i < node->num_keys && node->keys[i] < key) {
        i++;
    }
    if (i < node->num_keys && node->keys[i] == key) {
        for (int j = i; j < node->num_keys - 1; j++) {
            node->keys[j] = node->keys[j + 1];
            node->children[j] = node->children[j + 1];
        }
        node->children[node->num_keys - 1] = node->children[node->num_keys];
        node->num_keys--;
    }
}

// 从B+树中删除键值对
Node* delete(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    Node* currentNode = root;
    Node* parentNode = NULL;

    // 寻找要删除的键值对
    while (!currentNode->is_leaf) {
        int i;
        for (i = 0; i < currentNode->num_keys; i++) {
            if (currentNode->keys[i] > key) {
                break;
            }
        }
        parentNode = currentNode;
        currentNode = currentNode->children[i];
    }

    // 删除键值对
    deleteFromNode(currentNode, key);

    // 如果当前节点的键值对数量过少，则进行节点合并或重分配
    if (currentNode != root && currentNode->num_keys < (MAX_DEGREE - 1) / 2) {
        int index = 0;
        while (parentNode->children[index] != currentNode) {
            index++;
        }

        // 尝试向左兄弟节点借键值对
        if (index > 0 && parentNode->children[index - 1]->num_keys > (MAX_DEGREE - 1) / 2) {
            Node* sibling = parentNode->children[index - 1];
            for (int i = currentNode->num_keys; i > 0; i--) {
                currentNode->keys[i] = currentNode->keys[i - 1];
                currentNode->children[i] = currentNode->children[i - 1];
            }
            currentNode->children[0] = sibling->children[sibling->num_keys];
            currentNode->keys[0] = sibling->keys[sibling->num_keys - 1];
            sibling->num_keys--;
            currentNode->num_keys++;
        }
        // 尝试向右兄弟节点借键值对
        else if (index < parentNode->num_keys && parentNode->children[index + 1]->num_keys > (MAX_DEGREE - 1) / 2) {
            Node* sibling = parentNode->children[index + 1];
            currentNode->keys[currentNode->num_keys] = sibling->keys[0];
            currentNode->children[currentNode->num_keys + 1] = sibling->children[0];
            currentNode->num_keys++;
            sibling->num_keys--;
            for (int i = 0; i < sibling->num_keys; i++) {
                sibling->keys[i] = sibling->keys[i + 1];
                sibling->children[i] = sibling->children[i + 1];
            }
            sibling->children[sibling->num_keys] = sibling->children[sibling->num_keys + 1];
        }
        // 合并左兄弟节点或右兄弟节点
        else {
            if (index > 0) {
                Node* sibling = parentNode->children[index - 1];
                sibling->keys[sibling->num_keys] = currentNode->keys[0];
                sibling->children[sibling->num_keys + 1] = currentNode->children[0];
                sibling->num_keys++;
                for (int i = 0; i < currentNode->num_keys; i++) {
                    sibling->keys[sibling->num_keys] = currentNode->keys[i];
                    sibling->children[sibling->num_keys + 1] = currentNode->children[i + 1];
                    sibling->num_keys++;
                }
                parentNode->num_keys--;
                for (int i = index - 1; i < parentNode->num_keys; i++) {
                    parentNode->keys[i] = parentNode->keys[i + 1];
                    parentNode->children[i + 1] = parentNode->children[i + 2];
                }
                free(currentNode);
                currentNode = sibling;
            } else {
                Node* sibling = parentNode->children[index + 1];
                currentNode->keys[currentNode->num_keys] = sibling->keys[0];
                currentNode->children[currentNode->num_keys + 1] = sibling->children[0];
                currentNode->num_keys++;
                sibling->num_keys--;
                for (int i = 0; i < sibling->num_keys; i++) {
                    sibling->keys[i] = sibling->keys[i + 1];
                    sibling->children[i] = sibling->children[i + 1];
                }
                sibling->children[sibling->num_keys] = sibling->children[sibling->num_keys + 1];
                free(sibling);
            }
        }
    }

    // 如果根节点为空，更新根节点
    if (root->num_keys == 0) {
        Node* newRoot = root->children[0];
        free(root);
        root = newRoot;
    }

    return root;
}

// 示例用法
int main() {
    Node* root = NULL;

    // 插入键值对
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);

    // 删除键值对
    root = delete(root, 20);

    return 0;
}
