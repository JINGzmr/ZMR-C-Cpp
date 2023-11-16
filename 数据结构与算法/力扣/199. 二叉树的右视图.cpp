// 层次遍历、记录每层的深度
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> V;
        if(root==NULL)                  
            return V;

        queue<TreeNode*> Q;
        Q.push(root);
        Q.push(NULL);  // 标志每一层的结束
        TreeNode *t_prior = NULL;

        while (!Q.empty()) {
            TreeNode* t = Q.front();
            Q.pop();

            if (t == NULL) {
                V.push_back(t_prior->val);
                if (Q.empty()) {
                    break; // 如果队列为空，则退出循环
                }
                Q.push(NULL); // 否则，加入 NULL 标记下一层的结束
                t_prior = NULL; // 重置 t_prior 为下一层的开始
            } else {
                t_prior = t;
                if (t->left)
                    Q.push(t->left);
                if (t->right)
                    Q.push(t->right);
            }
        }
        return V;
    }
};