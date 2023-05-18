//二叉排序树（BST）
#include <stdio.h>
#include <stdlib.h>

// 二叉树结点的定义
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建新结点
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 向二叉排序树中插入结点
struct TreeNode* insertNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        // 如果树为空，则创建一个新结点作为根结点
        return createNode(value);
    }

    if (value < root->data) {
        // 如果插入值小于当前结点的值，递归地插入到左子树中
        root->left = insertNode(root->left, value);
    } else if (value > root->data) {
        // 如果插入值大于当前结点的值，递归地插入到右子树中
        root->right = insertNode(root->right, value);
    }

    // 返回插入后的根结点
    return root;
}

// 在二叉排序树中查找给定值
struct TreeNode* searchNode(struct TreeNode* root, int value) {
    if (root == NULL || root->data == value) {
        // 如果树为空或当前结点的值等于给定值，则返回当前结点
        return root;
    }

    if (value < root->data) {
        // 如果给定值小于当前结点的值，递归地在左子树中查找
        return searchNode(root->left, value);
    } else {
        // 如果给定值大于当前结点的值，递归地在右子树中查找
        return searchNode(root->right, value);
    }
}

// 在二叉排序树中删除给定值
struct TreeNode* deleteNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        // 如果树为空，直接返回
        return root;
    }

    if (value < root->data) {
        // 如果给定值小于当前结点的值，在左子树中删除
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        // 如果给定值大于当前结点的值，在右子树中删除
        root->right = deleteNode(root->right, value);
    } else {
        // 找到了要删除的结点

        // 如果要删除的结点没有子结点或只有一个子结点
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // 如果要删除的结点有两个子结点
        // 找到右子树中的最小结点，将其值复制到要删除的结点上，然后在右子树中删除最小结点
        struct TreeNode* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    // 返回删除后的根结点
    return root;
}

// 通过给定的数组构造二叉排序树
struct TreeNode* constructBST(int arr[], int size) {
    struct TreeNode* root = NULL;
    int i;
    for (i = 0; i < size; i++) {
        root = insertNode(root, arr[i]);
    }
    return root;
}

// 中序遍历二叉排序树（升序输出）
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 主函数
int main() {
    struct TreeNode* root = NULL;
    int arr[] = {5, 2, 7, 1, 3};

    // 构造二叉排序树
    root = constructBST(arr, 5);

    // 输出排序后的结果
    printf("In-order traversal of the binary search tree: ");
    inorderTraversal(root);
    printf("\n");

    // 查找结点
    int searchValue = 2;
    struct TreeNode* searchResult = searchNode(root, searchValue);
    if (searchResult != NULL) {
        printf("Node with value %d found\n", searchValue);
    } else {
        printf("Node with value %d not found\n", searchValue);
    }

    // 删除结点
    int deleteValue = 5;
    root = deleteNode(root, deleteValue);
    printf("In-order traversal after deleting node %d: ", deleteValue);
    inorderTraversal(root);
    printf("\n");

    return 0;
}
