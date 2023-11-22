#include <iostream>
#include <queue>
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
    int minDepth(TreeNode* root) {
        int h=0,tag=0;
        if (root == NULL) {
            return 0;
        }

        queue<TreeNode *> Q;
        Q.push(root);
        while (!Q.empty()) {
            h++;
            int size = Q.size();
            for (int i = 0; i < size; i++) {
                TreeNode *node = Q.front();
                Q.pop();
                if(node->left==NULL&&node->right==NULL)tag=1;
                if (node->left) Q.push(node->left);
                if (node->right) Q.push(node->right);
            }
            if(tag)break;
        }
        return h;
    }
};