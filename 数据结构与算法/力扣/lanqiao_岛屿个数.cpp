#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int dxx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dyy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void BFS(vector<vector<int>>& grid,
         queue<pair<int, int>>& q,
         vector<vector<int>>& v,
         int flag) {
    while (!q.empty()) {
        pair<int, int> newpoint, point = q.front();
        q.pop();
        if (flag == 2) {  // 说明是标志海能够到达的区域模块
            for (int i = 0; i < 8; i++) {
                int x = point.first + dxx[i];
                int y = point.second + dyy[i];
                if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
                    continue;
                if (grid[x][y] == 0) {
                    newpoint.first = x;
                    newpoint.second = y;
                    q.push(newpoint);
                    grid[x][y] = 2;
                }
            }
        }
        if (flag == 1) {  // 说明是统计岛屿个数模块
            for (int i = 0; i < 4; i++) {
                int x = point.first + dx[i];
                int y = point.second + dy[i];
                if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
                    continue;
                if (grid[x][y] == 1 && v[x][y] == 0) {
                    newpoint.first = x;
                    newpoint.second = y;
                    q.push(newpoint);
                    v[x][y] = 1;
                }
            }
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, n, num = 0;
        cin >> m >> n;
        vector<vector<int>> grid(m + 2, vector<int>(n + 2)),
            v(m + 2, vector<int>(n + 2));
        string str;
        for (int i = 0; i < m; i++) {
            cin >> str;
            for (int j = 0; j < n; j++) {
                grid[i + 1][j + 1] = str[j] - '0';
            }
        }

        // for(int i=0;i<m+2;i++){
        //     for(int j=0;j<n+2;j++){
        //         cout << grid[i][j];
        //     }
        //     cout << endl;
        // }

        // 从00开始,通过八个方向遍历地图,把是0的地方全部设置为2,表示外部海水能到达的区域

        queue<pair<int, int>> q;
        pair<int, int> point(0, 0);
        q.push(point);
        BFS(grid, q, v, 2);

        // 遍历一次地图,把所有0变为1.这样内部的子岛屿就和外部的岛屿连到一起了
        for (int i = 0; i < m + 2; i++) {
            for (int j = 0; j < n + 2; j++) {
                if (grid[i][j] == 0)
                    grid[i][j] = 1;
            }
        }

        // 正常BFS,找岛屿的个数即可
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (v[i][j] == 0 && grid[i][j] == 1) {
                    pair<int, int> point = make_pair(i, j);
                    q.push(point);
                    v[i][j] = 1;
                    num++;
                    BFS(grid, q, v, 1);
                }
            }
        }

        // 打印岛屿个数
        cout << num << endl;
    }
}
