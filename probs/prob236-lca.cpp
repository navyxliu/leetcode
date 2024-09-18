/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    // This is basically the recursive definition of LCA. it's not so straight-forward until you relate it
    // to the dominator tree in compiler. Sometimes a concept is so abstract that we have to make sense of it
    // by making an analogy.
    //
    // return a node that dominates both p and q =>
    // a node dominates itself;
    // or current node is dominator if left dominates one node and right dominates yet another;
    // or right is dominator if left can't dominate either.
    // or left is dominator if right can't dominate either.
    // or no dominator at all.
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }

        TreeNode* left = lca(root->left, p, q);
        TreeNode* right = lca(root->right, p, q);
        if (left != nullptr && right != nullptr) {
            return root;
        } else if (left == nullptr) {
            return right;
        } else if (right == nullptr) {
            return left;
        } else {
            return nullptr;
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lca(root, p, q);
    }
};