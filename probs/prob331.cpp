#include <stack>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std; 

class Solution {
public:
    bool isValidSerialization(string preorder) {
        stack<int> sp;
        int sz = preorder.size(); 
        if (sz == 0) return false; 
        if (sz == 1) {
            return preorder[0] == '#';
        }
        
        for (int i=0; i<sz; ++i) {
            if (preorder[i] == '#') {
              if(!popMe(sp)) return false; 
            }
            else {
                sp.push(2);
            }
            while (i<sz && preorder[i] != ',') i++; 
        }
        
        return sp.empty(); 
    }
    
    bool popMe(stack<int>& sp) {
        if (sp.empty()) return false; 
        
        while (!sp.empty()) {
            sp.top()--; 
            if (sp.top()>0) break;
            sp.pop();
        }
        return true; 
    }
};
int main() {
  Solution sol;
  cout << boolalpha << sol.isValidSerialization("9,#,#") << "\n";
}
