// prob129: Sum Root to Leaf Numbers
// Morris Preorder traversal
// it has O(1) space complexity because it leverages 'predecessor.right' to jump to the next node.
//
#include "leetcode.hpp"
#include "io.hpp"
#include "debug.hpp"

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        // Morris preorder traversal
        int ans = 0;
        TreeNode* curr = root;
        int val = 0;
        int steps = 0;

        while (curr != nullptr ) {
            if (curr->left == nullptr) {
                val = val * 10 + curr->val;
                if (curr->right == nullptr) {
                    ans += val;
                }
                //Morris: visit curr here.
                //cout << curr->val << " ";
                curr = curr->right;
            } else {
                steps = 1;
                TreeNode* predecessor = curr->left;
                while (predecessor->right != nullptr && predecessor->right != curr) {
                    steps++;
                    predecessor = predecessor->right;
                }
                if (predecessor->right == nullptr) {
                    //Morris: preorder visits curr here. 

                    //cout << curr->val << " ";
                    val = val * 10 + curr->val;
                    predecessor->right = curr;
                    // the left subtree has not visited yet, turn left.
                    curr = curr->left;
                } else {
                    if (predecessor->left == nullptr) {
                        ans += val;
                    }
                    for (int i = 0; i< steps; ++i) {
                        val /= 10;
                    }

                    // the left subtree has been visited.
                    // turn right and recover predecessor.
                    curr = curr->right;
                    predecessor->right = nullptr;
                    //Morris: inorder visits curr here.
                }
            }
        }
        return ans;
    }
};

int main() {
    // [1,2,3]
    TreeNode *root = build_binary_complete_tree({1, 2, 3});
    Solution sol;
    int ans = sol.sumNumbers(root);
    cout << ans << endl;

    // [4,9,0,5,1]
    root = build_binary_complete_tree({4,9,0,5,1});
    ans = sol.sumNumbers(root);
    cout << ans << endl;
}