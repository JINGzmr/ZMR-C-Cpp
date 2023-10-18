/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void traversal(vector<int>&result, TreeNode* root){ //用到的是引用，这样就能直接修改数组result的内容，而不用再创建一个相同的数组，往里加元素后再将其返回（这样占时间和空间）
        if(root==NULL) //没有是NULL，而不是nullptr
            return ;
        result.push_back(root->val);
        traversal(result,root->left);
        traversal(result,root->right);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(result,root);
        return result;
    }
};


