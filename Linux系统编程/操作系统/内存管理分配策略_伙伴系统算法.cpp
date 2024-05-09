#include <iostream>
#include <cmath>

// 定义内存块的最大大小
#define MAX_SIZE 1024

// 定义内存块的状态
enum BlockStatus { FREE, SPLIT, OCCUPIED };

// 定义内存块结构体
struct Block {
    int size;            // 内存块大小
    BlockStatus status;  // 内存块状态
    Block* prev;         // 上一个内存块的指针
    Block* next;         // 下一个内存块的指针
};

// 定义伙伴系统类
class BuddySystem {
   private:
    Block* memory;  // 内存块数组
    int totalSize;  // 总内存大小

   public:
    // 构造函数
    BuddySystem(int size) {
        totalSize =
            pow(2, ceil(log2(size)));  // 计算总内存大小，并向上取整为2的幂次方
        memory = new Block[totalSize];  // 创建内存块数组

        // 初始化第一个内存块
        memory[0].size = totalSize;
        memory[0].status = FREE;
        memory[0].prev = nullptr;
        memory[0].next = nullptr;
    }

    // 分配内存
    void* allocate(int size) {
        int blockSize = pow(
            2,
            ceil(log2(size)));  // 计算要分配的内存块大小，并向上取整为2的幂次方

        // 查找合适的内存块
        Block* block = findBlock(blockSize);
        if (block == nullptr) {
            std::cout << "无法分配内存块大小：" << size << std::endl;
            return nullptr;
        }

        // 切割内存块
        splitBlock(block, blockSize);

        // 标记内存块为已占用
        block->status = OCCUPIED;

        // 返回分配的内存块地址
        return reinterpret_cast<void*>(block);
    }

    // 释放内存
    void deallocate(void* address) {
        // 将地址转换为内存块指针
        Block* block = reinterpret_cast<Block*>(address);

        // 标记内存块为释放状态
        block->status = FREE;

        // 合并相邻的空闲内存块
        mergeBlocks(block);
    }

   private:
    // 查找合适的内存块
    Block* findBlock(int size) {
        // 从头开始遍历内存块数组
        for (int i = 0; i < totalSize; i++) {
            // 找到第一个合适的内存块
            if (memory[i].status == FREE && memory[i].size >= size) {
                return &memory[i];
            }
        }

        // 未找到合适的内存块
        return nullptr;
    }

    // 切割内存块
    void splitBlock(Block* block, int size) {
        // 终止条件：如果当前块的大小已经小于等于要分配的大小，则停止切割
        if (block->size <= size) {
            return;
        }
        // 检查是否需要继续切割
        while (block->size > size * 2) {
            // 计算切割后的内存块大小
            int newSize = block->size / 2;

            // 设置左子块
            block->next = block + newSize;
            block->next->prev = block;
            block->next->size = newSize;
            block->next->status = SPLIT;
            block->next->next = nullptr;

            // 设置右子块
            block->prev = block->next;
            block->prev->next = block;
            block->prev->size = newSize;
            block->prev->status = FREE;
            block->prev->prev = nullptr;

            // 更新当前块的大小和状态
            block->size = newSize;
            block->status = SPLIT;

            // 继续切割左子块
            block = block->next;
        }
    }

    // 合并相邻的空闲内存块
    void mergeBlocks(Block* block) {
        // 合并左侧的空闲内存块
        while (block->prev != nullptr && block->prev->status == FREE) {
            // 提取左侧的空闲内存块
            Block* leftBlock = block->prev;

            // 更新当前块的大小和状态
            block->size *= 2;
            block->status = FREE;

            // 更新左侧块的指针
            block->prev = leftBlock->prev;
            if (block->prev != nullptr) {
                block->prev->next = block;
            }

            // 删除左侧块
            leftBlock->status = FREE;
            leftBlock->prev = nullptr;
            leftBlock->next = nullptr;
        }

        // 合并右侧的空闲内存块
        while (block->next != nullptr && block->next->status == FREE) {
            // 提取右侧的空闲内存块
            Block* rightBlock = block->next;

            // 更新当前块的大小和状态
            block->size *= 2;
            block->status = FREE;

            // 更新右侧块的指针
            block->next = rightBlock->next;
            if (block->next != nullptr) {
                block->next->prev = block;
            }

            // 删除右侧块
            rightBlock->status = FREE;
            rightBlock->prev = nullptr;
            rightBlock->next = nullptr;
        }
    }
};

int main() {
    BuddySystem buddySystem(1024);

    // 分配内存块
    void* block1 = buddySystem.allocate(128);
    void* block2 = buddySystem.allocate(256);
    void* block3 = buddySystem.allocate(64);

    // 释放内存块
    buddySystem.deallocate(block2);

    return 0;
}