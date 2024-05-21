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
    vector<double> averageOfLevels(TreeNode *root) {
        vector<double> V;
        if (root == NULL) {
            return V;
        }

        queue<TreeNode *> Q;
        Q.push(root);
        while (!Q.empty()) {
            int size = Q.size();
            double sum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode *node = Q.front();
                Q.pop();
                sum += node->val;

                if (node->left) Q.push(node->left);
                if (node->right) Q.push(node->right);
            }
            V.push_back(1.0 * sum / size);
        }
        return V;
    }
};
