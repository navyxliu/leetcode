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
    int closestValue(TreeNode* root, double target) {
        int lower = findLower(root, target)->val;
        cout << "lower " << lower << "\n";
        if (lower >= target) return lower;
        
        int upper = findUpper(root, target)->val;
        cout << "upper " << upper << "\n";
        if (upper <= target) return upper; 
        
        double d1 = target - lower; 
        double d2 = upper - target; 
        if (d1 < d2) return lower; 
        else return upper; 
    }
    int rightMostValue(TreeNode * t) {
        int v;
        cout << "rightMostValue " << t->val << "\n";
        while (t) {v = t->val; t= t->right; }
        cout << "rightMostValue " << v << "\n";
        return v; 
    }
    int leftMostValue(TreeNode * t) {
        int v = t->val;
        while (t->left) {t= t->left; v = t->val;}
        return v; 
    }
    
    TreeNode * findUpper(TreeNode * r, double target) {
        TreeNode * t = r; 
        while (true) {
            if (t->val == target) break;
            else if (t->val < target) {
                if (!t->right) break;
                t = t->right; 
            }
            else {//t->val > target
                if (!t->left || rightMostValue(t->left) < target) break;
                t = t->left; 
            }
        }
        
        return t; 
    }
    
    TreeNode * findLower(TreeNode * r, double target) {
        TreeNode * t = r; 
        
        while (true) {
            if (t->val == target) break;
            else if (t->val < target) {
                if (!t->right || leftMostValue(t->right) > target) break;
                t = t->right; 
            }
            else {
                if (!t->left) break;
                t = t->left; 
            }
        }
        
        return t; 
    }
};

int main() {
  TreeNode * root = new TreeNode(8);
  root->left = new TreeNode(1);
  Solution sol; 
  cout << sol.findUpper(root, 6.0)->val << "\n";
}
