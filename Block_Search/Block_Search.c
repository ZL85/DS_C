//分块查找算法
#include <stdio.h>

// 定义每个块中的元素个数
#define BLOCK_SIZE 5

// 定义块的结构体
struct Block {
    int data[BLOCK_SIZE];  // 存储块中的元素
    int count;             // 当前块中的元素个数
};

// 分块查找函数
int blockSearch(struct Block blocks[], int numBlocks, int key) {
    int blockIndex = -1;  // 块索引
    int i;               // 循环变量

    // 找到关键字所在的块
    for (i = 0; i < numBlocks; i++) {
        if (key <= blocks[i].data[blocks[i].count - 1]) {
            blockIndex = i;
            break;
        }
    }

    // 在关键字所在的块中进行顺序查找
    if (blockIndex != -1) {
        for (i = 0; i < blocks[blockIndex].count; i++) {
            if (key == blocks[blockIndex].data[i]) {
                return key;  // 找到了关键字
            }
        }
    }

    return -1;  // 未找到关键字
}

int main() {
    // 初始化块
    struct Block blocks[] = {
        {{1, 2, 3, 4, 5}, 5},
        {{6, 7, 8, 9, 10}, 5},
        {{11, 12, 13, 14, 15}, 5},
        {{16, 17, 18, 19, 20}, 5}
    };

    int numBlocks = sizeof(blocks) / sizeof(blocks[0]);  // 块的数量

    int key;  // 要查找的关键字
    printf("Enter key to search: ");
    scanf("%d", &key);

    // 执行分块查找
    int result = blockSearch(blocks, numBlocks, key);

    // 根据查找结果输出信息
    if (result != -1) {
        printf("Key found: %d\n", result);
    } else {
        printf("Key not found.\n");
    }

    return 0;
}
/*
上述代码定义了一个块结构体 Block，其中包含一个整型数组 data 用于存储块中的元素，以及一个整型变量 count 表示当前块中的元素个数。
blockSearch 函数是分块查找的核心部分。它接受一个 Block 结构体数组 blocks、块的数量 numBlocks 和要查找的关键字 key 作为参数。
该函数首先遍历块数组，找到关键字所在的块索引 blockIndex。然后，在该块中顺序查找关键字，如果找到则返回关键字的值，否则返回 -1 表示未找到。
在 main 函数中，我们初始化了一个包含多个块的数组 blocks，并计算块的数量。
*/