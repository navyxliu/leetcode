#include <stack>
#include <iostream>
using namespace std; 

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if (root == NULL) return root; 
        
        TreeNode * t= root; 
        stack<TreeNode*> sp;
        while (t->left) {
            sp.push(t);
            t = t->left; 
        }
        cout << "after";
        TreeNode * ans = t; 
        while (!sp.empty()) {
            TreeNode * p = sp.top(); 
            sp.pop();

            t->left = p->right; 
            t->right = p;
            t = p;
        }
        t->left = t->right = NULL; 
        return ans; 
    }
};
void inorderImpl(TreeNode * p) {
  if (p->left) inorderImpl(p->left);
  cout << p->val << ",";
  if (p->right) inorderImpl(p->right);
}
void inorder(TreeNode *p) {
  cout << "["; 
  inorderImpl(p); 
  cout << "]\n";
}
int main() {
  Solution sol;
  TreeNode * r = new TreeNode(1);
  r->left = new TreeNode(2);
  TreeNode * ans = sol.upsideDownBinaryTree(r);
  inorder(ans);
}
