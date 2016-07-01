#include <unordered_map>
#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    unordered_map<TreeNode*, TreeNode *> ht;
    
    TreeNode * findRoot(TreeNode *t) {
        while (ht[t] != t) {
            t = ht[t];
        }
        
        return t;
    }
    
    TreeNode * tarjan(TreeNode *t, TreeNode * parent, TreeNode * p, TreeNode * q)
    {
        ht[t] = t;
        TreeNode * ans = NULL; 
 
        if (t->left) {
            ans = tarjan(t->left, t, p, q);
        }
        
        if (t->right && !ans)
            ans = tarjan(t->right, t, p, q);

        if (ans) return ans;
       
        ht[t] = parent;
        if (t == p && ht.find(q) != ht.end()) {
          return findRoot(q);
        }
        if (t == q && ht.find(p) != ht.end()) {
          return findRoot(p);
        }

        return NULL;
    }
    
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) {
            return NULL;
        }
        if (p == q) return p;
      
        ht.clear(); 
        
        return tarjan(root, NULL, p, q);
    }
};

ostream & operator<<(ostream& os, TreeNode* t) {
  os << t->val << "\n";
  return os;
}

int main() 
{
  TreeNode * p = new TreeNode(3);
    p->left = new TreeNode(5); 
      p->left->left = new TreeNode(6);
      p->left->right = new TreeNode(2);
        p->left->right->left = new TreeNode(7);
        p->left->right->right = new TreeNode(4);
    p->right = new TreeNode(1);
      p->right->left = new TreeNode(0);
      p->right->right = new TreeNode(8);

  Solution sol; 
  cout << sol.lowestCommonAncestor(p, p->left->left, p);
  cout << sol.lowestCommonAncestor(p, p->left, p->right);
  cout << sol.lowestCommonAncestor(p, p->left, p->left->right->right);
}

