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
          if (t->right) t->left->next = t->right; 
          else {
            TreeLinkNode * s = t->next; 

            while (s) {
              if (s->left) {
                t->left->next = s->left; 
                break;
              }
              else if (s->right) {
                t->left->next = s->right; 
                break;
              }

              s = s->next; 
            }
          } 
        }

        if (t->right) {
          TreeLinkNode * s = t->next; 

          while (s) {
            if (s->left) {
              t->right->next = s->left; 
              break;
            }
            else if (s->right) {
              t->right->next = s->right; 
              break;
            }
            s = s->next; 
          }
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

  //r->left->right = new TreeLinkNode(5);
  //r->left->right->right = new TreeLinkNode(6);
  //r->left->right->right->right = new TreeLinkNode(10); 

  r->left->left->left = new TreeLinkNode(8);
  r->left->left->left->right = new TreeLinkNode(12);

  r->right->right = new TreeLinkNode(7);
  r->right->right->right = new TreeLinkNode(9);
  r->right->right->right->right = new TreeLinkNode(11);

  sol.connect(r);
  sol.inorder(r);  
}
