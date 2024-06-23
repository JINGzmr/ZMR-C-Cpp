#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_SIZE 256 * 1024 * 1024 // 256GB
#define BLOCK_SIZE 4 * 1024 // 4KB
#define BITMAP_SIZE (DISK_SIZE / BLOCK_SIZE + 7) / 8 // 8MB
#define true 1

// 初始化位示图
void init_bitmap(char *bitmap) {
    memset(bitmap, 0, BITMAP_SIZE);
}

// 分配一个磁盘块
int alloc_block(char *bitmap) {
    for (int i = 0; i < DISK_SIZE / BLOCK_SIZE; i++) {
        if ((bitmap[i / 8] & (1 << (i % 8))) == 0) {
            bitmap[i / 8] |= (1 << (i % 8));
            return i;
        }
    }
    return -1; // 没有可用的磁盘块
}

// 释放一个磁盘块
void free_block(char *bitmap, int block_num) {
    bitmap[block_num / 8] &= ~(1 << (block_num % 8));
}

int main() {
    char *bitmap = (char *)malloc(BITMAP_SIZE);
    init_bitmap(bitmap);

    // 分配并释放磁盘块
    while (true) {
        int block = alloc_block(bitmap);
        if (block == -1) {
            printf("No more available blocks\n");
            break;
        }
        printf("Allocated block %d\n", block);
        // 在这里进行其他操作,比如释放磁盘块
        free_block(bitmap, block);
        printf("Freed block %d\n", block);
    }

    free(bitmap);
    return 0;
}