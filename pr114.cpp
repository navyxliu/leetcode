#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode * l; 
public:
    void flatten(TreeNode* root) {
        l = nullptr;
        inorder(root); 
    }

    void inorder(TreeNode * t) {
      if (t == NULL) return; 
      TreeNode *left = t->left; 
      TreeNode * right = t->right; 

      if (l == NULL) l = t;
      else {
        l->left = NULL; 
        l->right = t;         
        l = t;
      }
           
      inorder(left);
      inorder(right); 
    }
};

int main() {
  Solution sol; 
  
#if 1
//[1,2,null,3,4,5]
  TreeNode * r = new TreeNode(1);
  r->left = new TreeNode(2);
  r->left->left = new TreeNode(3);
  r->left->right = new TreeNode(4);
  r->left->left->left = new TreeNode(5);
#else

  TreeNode * r = new TreeNode(1);
  r->left = new TreeNode(2);
#endif
  sol.flatten(r);

  while (r) {
    cout << r->val << " - "; 
    r = r->right;
  }
  cout << "\n";
}
