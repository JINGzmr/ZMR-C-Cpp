#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/io.h>
#include <errno.h>

// 键盘端口地址
#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64

// 获取键盘输入
unsigned char get_scancode() {
    // 等待键盘控制器的输入缓冲区不为空
    while (1) {
        // 读取状态端口的值
        unsigned char status = inb(KBD_STATUS_PORT);
        // 检查状态中的第1位是否被置位，表示有数据可读
        if (status & 0x01) {
            // 从数据端口读取扫描码
            return inb(KBD_DATA_PORT);
        }
        // 短暂休眠，避免CPU占用过高
        usleep(1000);
    }
}

// 示例函数：映射显卡内存
void* map_memory(off_t base, size_t size) {
    int mem_fd;
    void *mapped_base;

    // 打开/dev/mem
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd == -1) {
        perror("open /dev/mem");
        exit(1);
    }

    // 内存映射
    mapped_base = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, base);
    if (mapped_base == MAP_FAILED) {
        perror("mmap");
        close(mem_fd);
        exit(1);
    }

    close(mem_fd);
    return mapped_base;
}

int main() {
    // 设置I/O特权级别为3（用户态），需要root权限
    if (iopl(3)) {
        perror("iopl");
        exit(1);
    }

    printf("Press any key to see its scancode...\n");

    // 获取按键扫描码
    unsigned char scancode = get_scancode();
    printf("Scancode: 0x%x\n", scancode);

    // 示例：映射显卡内存（假设地址为0xA0000，大小为4KB）
    void *mapped_mem = map_memory(0xA0000, 4096);
    // 访问映射的内存
    printf("Mapped memory value: 0x%x\n", *((unsigned char *)mapped_mem));
    // 取消映射
    if (munmap(mapped_mem, 4096) == -1) {
        perror("munmap");
        exit(1);
    }

    // 恢复I/O特权级别为0（内核态）
    if (iopl(0)) {
        perror("iopl");
        exit(1);
    }

    return 0;
}
