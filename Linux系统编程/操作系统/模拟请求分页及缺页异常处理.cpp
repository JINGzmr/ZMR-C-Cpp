#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// 模拟物理内存
const int PHYSICAL_MEMORY_SIZE = 4; // 物理内存页面数

// 模拟虚拟地址空间
const int VIRTUAL_MEMORY_SIZE = 8; // 虚拟内存页面数

// 模拟页表
vector<int> page_table(VIRTUAL_MEMORY_SIZE, -1);

// 模拟物理内存框架
vector<int> physical_memory(PHYSICAL_MEMORY_SIZE, -1);

// 页面访问历史,用于LRU算法
vector<int> page_access_history;

// 随机数生成器
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(0, VIRTUAL_MEMORY_SIZE - 1);

void handle_page_fault(int virtual_page_num) ;

int lru_replace_page() {
    // 使用LRU算法选择要替换的页面
    int page_to_replace = page_access_history[0];
    page_access_history.erase(page_access_history.begin());
    return page_to_replace;
}

void request_page(int virtual_page_num) {
    // 请求访问虚拟页面
    if (page_table[virtual_page_num] == -1) {
        // 缺页异常处理
        handle_page_fault(virtual_page_num);
    } else {
        // 页面命中
        int physical_page_num = page_table[virtual_page_num];
        page_access_history.push_back(virtual_page_num);
        cout << "访问虚拟页面" << virtual_page_num << ", 物理页面" << physical_page_num << endl;
    }
}

void handle_page_fault(int virtual_page_num) {
    // 缺页异常处理
    cout << "缺页异常, 访问虚拟页面" << virtual_page_num << endl;

    // 选择要替换的页面
    int replace_page_num = lru_replace_page();
    int replace_physical_page_num = page_table[replace_page_num];
    cout << "替换虚拟页面" << replace_page_num << ", 物理页面" << replace_physical_page_num << endl;

    // 将新页面装入物理内存
    auto free_frame = find(physical_memory.begin(), physical_memory.end(), -1);
    if (free_frame == physical_memory.end()) {
        // 物理内存已满,需要进行页面置换
        physical_memory[replace_physical_page_num] = -1;
    } else {
        // 分配新的物理页面
        *free_frame = virtual_page_num;
    }

    // 更新页表
    page_table[virtual_page_num] = distance(physical_memory.begin(), free_frame);
    page_access_history.push_back(virtual_page_num);
}

int main() {
    // 模拟页面访问
    for (int i = 0; i < 20; i++) {
        int virtual_page_num = dis(gen);
        request_page(virtual_page_num);
    }

    return 0;
}