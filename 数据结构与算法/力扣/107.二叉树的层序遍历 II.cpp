#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> V, result;
        if (root == NULL) {
            return V;
        }

        queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty()) {
            vector<int> Vec;
            int size = Q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = Q.front();
                Q.pop();
                Vec.push_back(node->val);

                if (node->left) Q.push(node->left);
                if (node->right) Q.push(node->right);
            }
            V.push_back(Vec);
        }
        // 法一：耗费空间
        // int size = V.size();
        // for (int i = 0; i < size; i++) {
        //     vector<int> t = V.back();
        //     V.pop_back();
        //     result.push_back(t);
        // }
        // return result;

        // 法二：调用函数
        reverse(V.begin(), V.end());
        return V;
    }
};