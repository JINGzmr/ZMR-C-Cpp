#include <iostream>
#include <vector>
#include <queue>
#include <utility>  //pair<,>
#include <cstring>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int num = 0; // 记录岛屿数量
        memset(v, 0, sizeof(v));
        pair<int, int> start = find(grid);
        if (start.first == -1)
            return 0;
        do {
            q.push(start);
            num++;
            v[start.first][start.second] = 1;

            while (!q.empty()) {
                BFS(grid);
            }

            start = find(grid);
        } while (start.first != -1);
        return num;
    }

private:
    pair<int, int> find(vector<vector<char>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '1' && v[i][j] == 0) { // 是陆地且未被访问过
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1); // 没找到
    }

    void BFS(vector<vector<char>>& grid) {
        pair<int, int> newt, t = q.front();
        for (int i = 0; i < 4; i++) {
            newt.first = t.first + dx[i];
            newt.second = t.second + dy[i];
            if (newt.first < 0 || newt.first >= grid.size() ||
                newt.second < 0 || newt.second >= grid[0].size())
                continue; // 该点超界
            if (v[newt.first][newt.second] == 0 &&
                grid[newt.first][newt.second] ==
                    '1') { // 该点未被访问过且是岛屿
                q.push(newt);
                v[newt.first][newt.second] = 1;
            }
        }
        q.pop();
    }

    int v[300][300]; // 是否被访问过
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    queue<pair<int, int>> q;
};