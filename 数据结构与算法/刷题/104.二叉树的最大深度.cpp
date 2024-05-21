#include <iostream>
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
    int maxDepth(TreeNode *root) {
        int h = 0;
        if (root == NULL) return h;
        int h1 = maxDepth(root->left);
        int h2 = maxDepth(root->right);
        return (h1 > h2 ? h1 : h2) + 1;
    }
};