#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        // BFS
        queue<vector<int>> q;
        vector<vector<int>> res;//存储ok的路径
        vector<int> road;
        road.push_back(0);
        q.push(road);
        while (!q.empty()) {
            vector<int> road = q.front();
            q.pop();
            int x = road.back();
            if(x == graph.size()-1){//这个路径的最后一个元素为终点，说明该路径ok
                res.push_back(road);
                continue;
            }
            for(int i=0;i<graph[x].size();i++){
                vector<int> newroad = road;
                newroad.push_back(graph[x][i]);
                q.push(newroad);
            }
        }
        return res;
    }
};