#include <stdio.h>
#include <stdlib.h>

// 定义红黑树的颜色
typedef enum Color {
    RED,
    BLACK
} Color;

// 定义红黑树的节点
typedef struct Node {
    int key;
    Color color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

// 创建一个新的红黑树节点
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;  // 新插入的节点默认为红色
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 左旋操作
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;  // 设置y节点为x的右子节点
    x->right = y->left;  // 将y的左子节点设置为x的右子节点

    if (y->left != NULL)
        y->left->parent = x;  // 更新y的左子节点的父节点

    y->parent = x->parent;  // 更新y的父节点

    if (x->parent == NULL)
        *root = y;  // 如果x是根节点，则将y设置为新的根节点
    else if (x == x->parent->left)
        x->parent->left = y;  // 如果x是其父节点的左子节点，则将y设置为x父节点的左子节点
    else
        x->parent->right = y;  // 如果x是其父节点的右子节点，则将y设置为x父节点的右子节点

    y->left = x;  // 将x设为y的左子节点
    x->parent = y;  // 更新x的父节点为y
}

// 右旋操作
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;  // 设置x节点为y的左子节点
    y->left = x->right;  // 将x的右子节点设置为y的左子节点

    if (x->right != NULL)
        x->right->parent = y;  // 更新x的右子节点的父节点

    x->parent = y->parent;  // 更新x的父节点

    if (y->parent == NULL)
        *root = x;  // 如果y是根节点，则将x设置为新的根节点
    else if (y == y->parent->left)
        y->parent->left = x;  // 如果y是其父节点的左子节点，则将x设置为y父节点的左子节点
    else
        y->parent->right = x;  // 如果y是其父节点的右子节点，则将x设置为y父节点的右子节点

    x->right = y;  // 将y设为x的右子节点
    y->parent = x;  // 更新y的父节点为x
}

// 插入修正操作
void insertFixup(Node** root, Node* newNode) {
    while (newNode != *root && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) {
            Node* uncle = newNode->parent->parent->right;

            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;         // Case 1: 叔节点是红色
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;           // Case 2: 叔节点是黑色，且当前节点是右子节点
                    leftRotate(root, newNode);
                }

                newNode->parent->color = BLACK;          // Case 3: 叔节点是黑色，且当前节点是左子节点
                newNode->parent->parent->color = RED;
                rightRotate(root, newNode->parent->parent);
            }
        } else {
            Node* uncle = newNode->parent->parent->left;

            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;         // Case 1: 叔节点是红色
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;           // Case 2: 叔节点是黑色，且当前节点是左子节点
                    rightRotate(root, newNode);
                }

                newNode->parent->color = BLACK;          // Case 3: 叔节点是黑色，且当前节点是右子节点
                newNode->parent->parent->color = RED;
                leftRotate(root, newNode->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;  // 根节点总是黑色
}

// 插入节点
void insertNode(Node** root, int key) {
    Node* newNode = createNode(key);
    Node* y = NULL;
    Node* x = *root;

    // 找到插入位置
    while (x != NULL) {
        y = x;

        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;

    if (y == NULL)
        *root = newNode;  // 树为空，将新节点设为根节点
    else if (key < y->key)
        y->left = newNode;
    else
        y->right = newNode;

    insertFixup(root, newNode);  // 插入修正操作
}

// 删除修正操作
void deleteFixup(Node** root, Node* x, Node* xParent) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == xParent->left) {
            Node* sibling = xParent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;                      // Case 1: 兄弟节点是红色
                xParent->color = RED;
                leftRotate(root, xParent);
                sibling = xParent->right;
            }

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;                         // Case 2: 兄弟节点和其子节点都是黑色
                x = xParent;
                xParent = xParent->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;              // Case 3: 兄弟节点是黑色，且其左子节点是红色
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = xParent->right;
                }

                sibling->color = xParent->color;                // Case 4: 兄弟节点是黑色，且其右子节点是红色
                xParent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, xParent);
                x = *root;
                break;
            }
        } else {
            Node* sibling = xParent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;                      // Case 1: 兄弟节点是红色
                xParent->color = RED;
                rightRotate(root, xParent);
                sibling = xParent->left;
            }

            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;                         // Case 2: 兄弟节点和其子节点都是黑色
                x = xParent;
                xParent = xParent->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;              // Case 3: 兄弟节点是黑色，且其右子节点是红色
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = xParent->left;
                }

                sibling->color = xParent->color;                // Case 4: 兄弟节点是黑色，且其左子节点是红色
                xParent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, xParent);
                x = *root;
                break;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}

// 删除节点
void deleteNode(Node** root, int key) {
    Node* z = *root;

    // 找到待删除的节点
    while (z != NULL) {
        if (key == z->key)
            break;
        else if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL)
        return;  // 未找到待删除的节点

    Node* x = NULL;
    Node* xParent = NULL;

    // 如果z的子节点中有一个为空，或者两个都为空，则直接删除z节点
    if (z->left == NULL || z->right == NULL) {
        Node* y = z;
        x = (y->left != NULL) ? y->left : y->right;
        xParent = y->parent;

        if (x != NULL)
            x->parent = xParent;

        if (xParent == NULL)
            *root = x;  // 如果y是根节点的子节点，则将x设为新的根节点的子节点
        else if (y == xParent->left)
            xParent->left = x;  // 如果y是其父节点的左子节点，则将x设为y父节点的左子节点
        else
            xParent->right = x;  // 如果y是其父节点的右子节点，则将x设为y父节点的右子节点

        if (y != z)
            z->key = y->key;  // 如果y不是z节点本身，则将y的关键字赋值给z

        if (y->color == BLACK)
            deleteFixup(root, x, xParent);  // 删除修正操作

        free(y);
    } else {
        // 找到z的后继节点y（即右子树的最左节点）
        Node* y = z->right;

        while (y->left != NULL)
            y = y->left;

        x = y->right;
        xParent = y->parent;

        if (x != NULL)
            x->parent = xParent;

        if (xParent == NULL)
            *root = x;  // 如果y是根节点的子节点，则将x设为新的根节点的子节点
        else
            xParent->left = x;  // 否则，将x设为y父节点的左子节点

        z->key = y->key;  // 将y的关键字赋值给z

        if (y->color == BLACK)
            deleteFixup(root, x, xParent);  // 删除修正操作

        free(y);
    }
}

// 中序遍历红黑树（用于验证树的正确性）
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// 测试红黑树算法
int main() {
    Node* root = NULL;

    // 插入节点
    insertNode(&root, 10);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 15);
    insertNode(&root, 25);
    insertNode(&root, 5);

    // 输出红黑树
    printf("Inorder traversal of Red-Black Tree: ");
    inorderTraversal(root);
    printf("\n");

    // 删除节点
    deleteNode(&root, 20);

    // 输出红黑树
    printf("Inorder traversal after deleting a node: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
