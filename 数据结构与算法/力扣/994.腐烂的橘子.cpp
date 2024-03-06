#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct point {
    int x;
    int y;
    int step;
};                          // 队列里每个元素
queue<point> r;             // 申请队列
int dx[4] = {1, 0, -1, 0};  // 向四个方向延伸，顺序为：右 下 左 上
int dy[4] = {0, -1, 0, 1};
int v[10][10]; 
int INF = 10000;

class Solution {
   public:
    int orangesRotting(vector<vector<int>>& grid) {
        // 找腐烂的橘子
        int startx, starty;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 2) {
                    v[i][j] = 0;  // 腐烂橘子腐烂的时间为0
                    point t;
                    t.x = i;
                    t.y = j;
                    t.step = 0;
                    r.push(t);  // 把烂橘子全部放到队列里去
                } else if (grid[i][j] == 1) {
                    v[i][j] = INF;  // 新鲜橘子腐烂时间要开始为无穷大
                } else {
                    v[i][j] = -1;  // 空位不会腐烂
                }
            }
        }

        // BFS
        while (!r.empty()) {
            int x = r.front().x;  // 取队首元素的x坐标
            int y = r.front().y;  // 取队首元素的y坐标
            int step = r.front().step;
            cout << x << " " << y << " " << step << endl;

            for (int k = 0; k <= 3; k++) {  // 向四个方向拓展
                int newx, newy;
                newx = x + dx[k];
                newy = y + dy[k];
                if(newx<0||newx>=grid.size()||newy<0||newy>=grid[0].size()){ // 新拓展点越界了
                    continue;
                }
                if (v[newx][newy] != -1 &&
                    v[newx][newy] != 0)  // 该拓展点有橘子且未被访问过
                {
                    point newpoint;
                    newpoint.x = newx;
                    newpoint.y = newy;
                    newpoint.step = step + 1;

                    if (newpoint.step <= v[newx][newy]) {
                        v[newx][newy] = newpoint.step;
                        r.push(newpoint);  // 新拓展点入队
                    }
                }
            }
            r.pop();  // 拓展完后将队首元素出队
        }

        //寻找是否存在未腐烂的橘子 
        int max=0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (v[i][j]>max) {
                    max = v[i][j];
                }
            }
        }
        if(max==INF){
            return -1;

        }else{
            return max;
        }
    }
};