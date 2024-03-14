#include <iostream>
#include <vector>
#include <queue>
#include <utility>  //pair<,>
#include <cstring>
using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int num = 0; // 记录飞地数量
        memset(v, 0, sizeof(v));
        pair<int, int> start = find(grid);
        if (start.first == -1)
            return 0;
        do {
            int n = 0;
            int flag = 1;
            q.push(start);
            v[start.first][start.second] = 1;

            while (!q.empty()) {
                bool a = BFS(grid);
                if (a == true)
                    n++;
                else
                    flag = 0;
            }
            if (flag)
                num += n;

            start = find(grid);
        } while (start.first != -1);
        return num;
    }

private:
    pair<int, int> find(vector<vector<int>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 1 && v[i][j] == 0) { // 是陆地且未被访问过
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1); // 没找到
    }

    bool BFS(vector<vector<int>>& grid) {
        bool a = true;
        pair<int, int> newt, t = q.front();
        if (t.first == 0 || t.first == grid.size() - 1 ||
            t.second == 0 || t.second == grid[0].size() - 1)
            a = false; // 该点在边界，即不是飞地
            
        for (int i = 0; i < 4; i++) {
            newt.first = t.first + dx[i];
            newt.second = t.second + dy[i];
            if (newt.first < 0 || newt.first >= grid.size() ||
                newt.second < 0 || newt.second >= grid[0].size())
                continue; // 该点超界
            if (v[newt.first][newt.second] == 0 &&
                grid[newt.first][newt.second] ==
                    1) { // 该点未被访问过且不在边界
                if (newt.first == 0 || newt.first == grid.size() - 1 ||
                    newt.second == 0 || newt.second == grid[0].size() - 1)
                    a = false; // 该点在边界，即不是飞地
                q.push(newt);
                v[newt.first][newt.second] = 1;
            }
        }
        q.pop();
        return a;
    }

    int v[300][300]; // 是否被访问过
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    queue<pair<int, int>> q;
};