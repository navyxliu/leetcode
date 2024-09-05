#ifndef __IO_HPP__
#define __IO_HPP__
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(-1), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* build_binary_complete_tree(const vector<int>& input);
std::string pp(TreeNode *root);
#endif // __IO_HPP__
