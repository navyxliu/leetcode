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
    struct InorderIter {
        stack<TreeNode *> sp; 
        
        InorderIter(TreeNode * root) {
            prep(root);    
        }
        void prep(TreeNode * p) {
            while (p != NULL) {
                sp.push(p);
                p = p->left; 
            }
        }
        
        TreeNode * next() {
            TreeNode * p = sp.top();
            sp.pop();
            prep(p->right);
            return p; 
        }
        bool hasNext() const { return !sp.empty(); }
    };
    
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        InorderIter it(root);

        while (it.hasNext() && p != it.next());
        
        return it.hasNext()? it.next() : NULL;
    }
};
int main()
{

}
