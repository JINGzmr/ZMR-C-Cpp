#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

int main() {
    nlohmann::json jsonData = {1, 2, 3, 4, 5}; // JSON 数组

    // 将 JSON 数组转换为 std::vector<int>
    std::vector<int> destinationVector = jsonData.get<std::vector<int>>();

    // 输出目标容器的内容
    for (const auto& value : destinationVector) {
        std::cout << value << " ";
    }

    return 0;
}
