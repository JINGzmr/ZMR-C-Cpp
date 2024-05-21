#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

class Solution {
   public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int num = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 1) {
                    for (int k = 0; k < 4; k++) {
                        int x = dx[k] + i;
                        int y = dy[k] + j;
                        if (x < 0 || y < 0 || x >= grid.size() ||
                            y >= grid[0].size() || grid[x][y] == 0) {
                            num++;
                        }
                    }
                }
            }
        }
        return num;
    }
};