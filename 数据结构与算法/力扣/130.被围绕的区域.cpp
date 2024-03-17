#include <iostream>
#include <vector>
#include <queue>
#include <utility>  //pair<,>
#include <cstring>
using namespace std;

class Solution {
   public:
    void solve(vector<vector<char>>& board) {
        memset(v, 0, sizeof(v));
        find(board);

        while (!q.empty()) {
            BFS(board);
        }

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 'O' && v[i][j] == 0) {
                    board[i][j] = 'X';
                }
            }
        }
    }

   private:
    void find(vector<vector<char>>& board) {
        pair<int, int> point = make_pair(-1,-1);
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 'O' && v[i][j] == 0)  // 是O且未被访问过
                    if (i == 0 || i == board.size() - 1 || j == 0 ||
                        j == board[0].size() - 1) {  // 是边界
                        v[i][j] = 1;
                        point = make_pair(i, j);
                        q.push(point);
                    }
            }
        }
    }

    void BFS(vector<vector<char>>& board) {
        pair<int, int> newt, t = q.front();
        for (int i = 0; i < 4; i++) {
            newt.first = t.first + dx[i];
            newt.second = t.second + dy[i];
            if (newt.first < 0 || newt.first >= board.size() ||
                newt.second < 0 || newt.second >= board[0].size())
                continue;  // 该点超界
            if (v[newt.first][newt.second] == 0 &&
                board[newt.first][newt.second] ==
                    'O') {  // 该点未被访问过且有O
                q.push(newt);
                v[newt.first][newt.second] = 1;
            }
        }
        q.pop();
    }

    int v[300][300];  // 是否被访问过
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    queue<pair<int, int>> q;
};