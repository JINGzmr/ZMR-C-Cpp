// 银行家算法是一种用于预防死锁的策略，
//它确保系统能安全地分配资源给进程，以防止出现无法继续执行的情况
#include<stdio.h>

// 定义系统中的资源数量
#define NUM_RESOURCES 3
#define NUM_PROCESSES 5

// 初始可用资源数量
int available[NUM_RESOURCES] = {10, 5, 7};

// 最大需求资源数量
int max[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

// 已分配资源数量
int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

// 剩余需求资源数量
int need[NUM_PROCESSES][NUM_RESOURCES];

// 安全性检查函数
int isSafe(int process, int available[], int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES]) {
    // 判断当前进程所需的资源是否小于等于系统当前可用资源
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        if (need[process][i] > available[i])
            return 0;
    }
    return 1;
}

int main() {
    // 计算每个进程的剩余需求资源数量
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // 模拟进程的安全性检查
    int finish[NUM_PROCESSES] = {0};
    int safeSequence[NUM_PROCESSES];
    int count = 0;
    while (count < NUM_PROCESSES) {
        int found = 0;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i] && isSafe(i, available, allocation, need)) {
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    available[j] += allocation[i][j];
                }
                safeSequence[count++] = i;
                finish[i] = 1;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("System is in unsafe state!\n");
            return 1;
        }
    }

    // 打印安全序列
    printf("Safe sequence:");
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        printf(" P%d", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
