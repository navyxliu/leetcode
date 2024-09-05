#include "leetcode.hpp"
#include "io.hpp"

TreeNode* build_binary_complete_tree(const vector<int>& data) {
    TreeNode* root = nullptr;
    queue<TreeNode*> queue;
    auto it = data.begin();

    while (it != data.end()) {
        if (queue.empty()) {
            root = new TreeNode(*it);
            queue.push(root);
        } else { 
            TreeNode* curr = queue.front();
            TreeNode* node = new TreeNode(*it);
            if (curr->left == nullptr)  {
                curr->left = node; 
            } else {
                curr->right = node;
                queue.pop();
            }
            queue.push(node);
        }
        it++;
    }
    return root;
}

std::string pp(TreeNode *root) {
    std::stringstream ss;
    queue<TreeNode*> queue;

    bool first = true;
    ss << "[" ;

    if (root != nullptr) {
        queue.push(root);
    }

    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop();

        if (!first) {
            ss << " ,";
        } else {
            first = false;
        }

        if (node == nullptr) {
            ss << "null";
        } else {
            ss << node->val;
            queue.push(node->left);
            queue.push(node->right);
        }      
    }
    ss << "]";
    return ss.str();
}