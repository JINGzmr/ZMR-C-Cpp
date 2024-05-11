#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096              // 页的大小
#define PAGE_TBL_SIZE 1024          // 页表的大小
#define MEM_SIZE (1024 * 1024 * 4)  // 物理内存空间的大小

int page_tbl[PAGE_TBL_SIZE];  // 页表，保存物理页面号
char memory[MEM_SIZE];        // 模拟物理内存空间

// 初始化页表
void init_page_table() {
    for (int i = 0; i < PAGE_TBL_SIZE; i++) {
        page_tbl[i] = -1;  // -1 表示无内容
    }
}

// 计算虚拟地址的页号和偏移量
int get_page_offset(int virtual_addr) {
    return virtual_addr & (PAGE_SIZE - 1);
}

int get_page_num(int virtual_addr) {
    return virtual_addr / PAGE_SIZE;
}

// 计算虚拟地址对应的物理地址
char* translate_addr(int virtual_addr) {
    int page_num = get_page_num(virtual_addr);
    int page_offset = get_page_offset(virtual_addr);

    if (page_tbl[page_num] == -1) {
        // 若所需页面未分配，则分配一个物理页面
        int free_frame_num = -1;
        for (int i = 0; i < MEM_SIZE / PAGE_SIZE; i++) {
            if (page_tbl[i] == -1) {
                free_frame_num = i;
                break;
            }
        }

        if (free_frame_num != -1) {
            page_tbl[page_num] = free_frame_num;
        } else {
            // 若无法分配页面，则返回错误
            printf("Out of memory!\n");
            return NULL;
        }
    }

    return memory + page_tbl[page_num] * PAGE_SIZE + page_offset;
}

int main() {
    init_page_table();  // 初始化页表

    // 映射虚拟地址到物理地址并打印
    int virtual_addr, value;
    printf("Input virtual address and value separated by space: ");
    scanf("%x %d", &virtual_addr, &value);

    char* real_addr = translate_addr(virtual_addr);
    if (real_addr != NULL) {
        *((int*)real_addr) = value;
        printf("Virtual Address: %x -> Physical Address: %x\n", virtual_addr,
               (int)real_addr);
    }

    return 0;
}