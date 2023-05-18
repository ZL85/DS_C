// 平衡二叉树（ALV）
#include <stdio.h>
#include <stdlib.h>

// 平衡二叉树节点结构
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height; // 存储节点的高度信息
} Node;

// 计算节点的高度
int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// 计算两个数中的较大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 创建新节点
Node* newNode(int key) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// 右旋操作
Node* rightRotate(Node* y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// 左旋操作
Node* leftRotate(Node* x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 获取节点的平衡因子
int getBalance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// 查找节点
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// 插入节点
Node* insert(Node* node, int key) {
    // 执行标准的BST插入
    if (node == NULL) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        // 忽略重复的键
        return node;
    }

    // 更新节点的高度
    node->height = 1 + max(height(node->left), height(node->right));

    // 获取节点的平衡因子
    int balance = getBalance(node);

    // 平衡维护
    if (balance > 1 && key < node->left->key) {
        // 插入的节点位于左子树的左侧
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        // 插入的节点位于右子树的右侧
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        // 插入的节点位于左子树的右侧
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        // 插入的节点位于右子树的左侧
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

// 返回未修改的节点指针
    return node;
}

// 查找最小值节点
Node* minValueNode(Node* node) {
    Node *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// 删除节点
Node* deleteNode(Node* root, int key) {
// 执行标准的BST删除
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // 找到要删除的节点

        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;

            // 没有子节点的情况
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // 一个子节点的情况
                *root = *temp; // 将子节点的内容复制到当前节点
            }
            free(temp);
        } else {
            // 有两个子节点的情况
            Node *temp = minValueNode(root->right);

            // 将右子树中的最小值节点的键值替换当前节点的键值
            root->key = temp->key;

            // 删除右子树中的最小值节点
            root->right = deleteNode(root->right, temp->key);
        }
    }

// 如果树中只有一个节点，则返回
    if (root == NULL) {
        return root;
    }

// 更新节点的高度
    root->height = 1 + max(height(root->left), height(root->right));

// 获取节点的平衡因子
    int balance = getBalance(root);

// 平衡维护
    if (balance > 1 && getBalance(root->left) >= 0) {
        // 删除操作导致左子树不平衡，且左子树的左子树较高
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        // 删除操作导致左子树不平衡，且左子树的右子树较高
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        // 删除操作导致右子树不平衡，且右子树的右子树较高
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        // 删除操作导致右子树不平衡，且右子树的左子树较高
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

// 返回未修改的节点指针
    return root;
}

// 中序遍历二叉树
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// 构造平衡二叉树
Node* constructBalancedBST(int arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }

// 计算中间元素的索引
    int mid = (start + end) / 2;

// 创建根节点
    Node *root = newNode(arr[mid]);

// 递归构造左子树和右子树
    root->left = constructBalancedBST(arr, start, mid - 1);
    root->right = constructBalancedBST(arr, mid + 1, end);

// 更新节点的高度
    root->height = 1 + max(height(root->left), height(root->right));

    return root;
}

int main() {
    Node *root = NULL;

// 示例用法
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Inorder traversal of the balanced binary tree: ");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 10);

    printf("Inorder traversal of the balanced binary tree after deletion: ");
    inorderTraversal(root);
    printf("\n");

// 构造平衡二叉树示例
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node *balancedBST = constructBalancedBST(arr, 0, n - 1);

    printf("Inorder traversal of the constructed balanced binary search tree: ");
    inorderTraversal(balancedBST);
    printf("\n");

    return 0;
}