/*栈（Stack）数据结构： 栈是一种数据结构，它遵循先进后出（LIFO，Last In First Out）的原则。在这个问题中，栈被用来存储可能的移动路径。当需要回退时，可以从栈中弹出元素，模拟递归调用栈的行为。

循环结构： 非递归版本使用了循环结构（while循环）来迭代处理栈中的元素。每次循环迭代都相当于模拟递归的一层调用，直到栈为空。

结构体（Struct）： 结构体被用来存储栈中的元素。在这个问题中，结构体包含了位置信息和移动步数。

条件判断和逻辑运算： 在非递归版本中，使用条件判断语句（if语句）来确定下一步的可走位置，以及使用逻辑运算符来组合条件，确保选择合适的路径。

算法设计： 非递归版本中使用了一种贪心算法，每次选择下一步中度数最小的位置，以减少搜索的分支数。这种策略被称为贪心策略，是一种常见的优化算法。

错误处理： 在程序中进行错误检查，例如检查栈是否为空，以避免访问空栈的情况。*/

#include <stdio.h>
#include <stdlib.h>

// 马的移动方式，x和y分别表示在横纵方向上的移动距离
int move_x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int move_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int board[8][8] ;  // 棋盘

// 定义坐标结构体
typedef struct {
    int x;
    int y;
} Position;

// 定义栈元素结构体
typedef struct {
    Position pos;
    int move_count;
} StackElement;

// 打印棋盘
void printBoard() {
    printf("解决方案：\n");
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

// 检查坐标是否在合法范围内
int isValid(int x, int y) {
    return (x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == -1);
}

// 获取某个位置的下一步可走的位置数量
int getDegree(int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        if (isValid(x + move_x[i], y + move_y[i])) count++;
    }
    return count;
}

// 使用非递归的方式解决骑士周游问题
int solve(int startX, int startY) {
    int move_count = 2;
    StackElement stack[64];
    int top = 0;

    // 设置起始位置为已访问，并将起始位置入栈
    board[startX][startY] = 1;
    Position startPos = {startX, startY};
    stack[top++] = (StackElement) {startPos, move_count};

    while (top > 0) {
        StackElement current = stack[--top];
        move_count = current.move_count;
        Position currentPosition = current.pos;

        // 如果找到解决方案，打印棋盘并返回
        if (move_count == 65) {
            printBoard();
            return 1;
        }

        int min_deg_idx = -1;
        int min_deg = 9;

        // 寻找下一步的可走位置，并选择下一步移动到可走位置中度数最小的位置
        for (int i = 0; i < 8; ++i) {
            int next_x = currentPosition.x + move_x[i];
            int next_y = currentPosition.y + move_y[i];
            if (isValid(next_x, next_y)) {
                int degree = getDegree(next_x, next_y);
                if (degree < min_deg) {
                    min_deg = degree;
                    min_deg_idx = i;
                }
            }
        }

        // 如果有可走位置，将下一步入栈，并标记为已访问
        if (min_deg_idx != -1) {
            int next_x = currentPosition.x + move_x[min_deg_idx];
            int next_y = currentPosition.y + move_y[min_deg_idx];
            board[next_x][next_y] = move_count;
            stack[top++] = (StackElement) {{next_x, next_y}, move_count + 1};
        }
    }

    // 未找到解决方案
    return 0;
}

int main() {
    int startX, startY;

    // 输入起始坐标
    printf("请输入起始位置坐标 x y: \n");
    scanf("%d %d", &startX, &startY);

    // 检查输入的坐标是否在合法范围内
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8) {
        printf("输入的坐标范围应在 0 ~ 7 !\n");
        return 1;
    }

    // 初始化棋盘
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = -1;
        }
    }

    // 检查起始位置是否合法
    if (!isValid(startX, startY)) {
        printf("起始位置不合法！\n");
        return 1;
    }

    // 调用solve函数解决问题
    if (solve(startX, startY) == 0) {
        printf("没有找到正确的路径!\n");
    }

    return 0;
}

