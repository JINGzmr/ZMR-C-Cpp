#include <iostream>
#include <queue>
using namespace std;

class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        if (root == NULL) {
            return NULL;
        }

        queue<Node*> Q;
        Q.push(root);
        Q.push(NULL);  // 标志每一层的结束
        Node *t_prior = NULL;

        while (!Q.empty()) {
            Node* t = Q.front();
            Q.pop();

            if (t == NULL) {
                if (Q.empty()) {
                    break; // 如果队列为空，则退出循环
                }
                Q.push(NULL); // 否则，加入 NULL 标记下一层的结束
                t_prior = NULL; // 重置 t_prior 为下一层的开始
            } else {
                if (t_prior) {
                    t_prior->next = t;
                }
                t_prior = t;

                if (t->left)
                    Q.push(t->left);
                if (t->right)
                    Q.push(t->right);
            }
        }
        return root;
    }
};

