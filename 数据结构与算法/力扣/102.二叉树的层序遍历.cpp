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
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> V;
        if (root == NULL) {
            return V;
        }

        queue<TreeNode *> Q;
        Q.push(root);
        while (!Q.empty()) {
            int size = Q.size();
            vector<int> Vec;
            for (int i = 0; i < size; i++) {
                TreeNode *node = Q.front();
                Q.pop();
                Vec.push_back(node->val);
                if (node->left) Q.push(node->left);
                if (node->right) Q.push(node->right);
            }
            V.push_back(Vec);
        }
        return V;
    }
};