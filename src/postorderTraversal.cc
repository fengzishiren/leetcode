/*
 Binary Tree Postorder Traversal
 Given a binary tree, return the postorder traversal of its nodes' values.

 For example:
 Given binary tree {1,#,2,3},
 1
 2
 /
 3
 return [3,2,1].

 Note: Recursive solution is trivial, could you do it iteratively?
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
* Definition for binary tree
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> nodes;
        stack<TreeNode *> stack;
        if (!root)
            return nodes;
        stack.push(root);
        TreeNode *prev = root;
        TreeNode *node = root->left;

        while (!stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            while (!node->right || prev == node->right) {
                nodes.push_back(node->val);
                prev = node;
                stack.pop();
                if (stack.empty())
                    break;
                node = stack.top();
            }
            node = node->right;
        }
        return nodes;
    }

    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> vt;
        if (!root) return vt;
        stack<TreeNode *> s;
        TreeNode *p = root;
        while (p != NULL || !s.empty()) {
            while (p != NULL) {
                vt.push_back(p->val);
                s.push(p);
                p = p->left;
            }
            if (!s.empty()) {
                p = s.top();
                s.pop();
                p = p->right;
            }
        }
    }
};

int main(int argc, char **argv) {

    return 0;
}

