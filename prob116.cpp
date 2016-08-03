#include <stdlib.h>
#include <iostream>
using namespace std; 

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        populate(root);     
    }
    
    void populate(TreeLinkNode* t) {
        if (!t) return;


        if (t->left) {
            t->left->next = t->right; 
        }
        if (t->right && t->next) {
            t->right->next = t->next->left; 
        }
        
        populate(t->right);
        populate(t->left); 
    }
    void inorder(TreeLinkNode *t) {
      if (!t) return ;

      inorder(t->left);

      cout << t->val << " " << t->next; 
      if (t->next) {
        cout << "(" << t->next->val << ")";
      }
      cout << "\n";

      inorder(t->right); 
    }
};

int main() {
  Solution sol; 
  TreeLinkNode * r = new TreeLinkNode(1);
  r->left = new TreeLinkNode(2);
  r->right = new TreeLinkNode(3);
  r->left->left = new TreeLinkNode(4);
  r->left->right = new TreeLinkNode(5);
  r->right->left = new TreeLinkNode(6);
  r->right->right = new TreeLinkNode(7);
 
  sol.connect(r);
  sol.inorder(r);  
}
