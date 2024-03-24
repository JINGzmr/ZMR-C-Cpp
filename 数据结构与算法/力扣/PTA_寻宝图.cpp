#include<bits/stdc++.h>
using namespace std;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int BFS(vector<vector<int>> &grid,queue<pair<int,pair<int,int>>> &q,vector<vector<int>> &v)
{
    int flag = 0;
    while(!q.empty()){
        pair<int,pair<int,int>> newpoint,point = q.front();
        q.pop();
        if(point.second.second>1)
            flag = 1;//说明确实有宝藏

        for(int i=0;i<4;i++){
            int x = point.first + dx[i];
            int y = point.second.first + dy[i];
            if(x<0||y<0||x>=grid.size()||y>=grid[0].size())continue;
            if(v[x][y]==0&&grid[x][y]!=0){
                v[x][y] = 1;
                newpoint = make_pair(x,make_pair(y,grid[x][y]));
                q.push(newpoint);
            }
        }
    }
    return flag;
}

int main()
{
    int n,m,num = 0,velnum = 0;
    cin >> n >> m;
    vector<vector<int>> grid(n,vector<int>(m)),v(n,vector<int>(m));
    queue<pair<int,pair<int,int>>> q;
    for(int i=0;i<n;i++){
        string str;
        cin >> str;
        for(int j=0;j<m;j++){
            grid[i][j] = str[j]-'0';
        }
    }

    for(int i =0;i<n;i++)
    {
        for(int j=0;j<m;j++){
            if(v[i][j]==0&&grid[i][j]!=0){
                v[i][j]=1;
                pair<int,pair<int,int>> point = make_pair(i,make_pair(j,grid[i][j]));
                q.push(point);
                num ++ ;
                int flag = BFS(grid,q,v);
                if(flag == 1)velnum++;
            }
        }
    }

    cout << num << " " << velnum;
}