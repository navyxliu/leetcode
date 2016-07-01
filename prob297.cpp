#include <vector>
#include <stack>
#include <iostream>
#include <sstream>
#include <string>
using namespace std; 

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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


class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
      if (root == NULL) return "()";    
      stringstream ss; 
      ss << "(" << root->val << ",";
      ss << serialize(root->left) << ",";
      ss << serialize(root->right) << ")"; 
      return ss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
//      cout << "deserialize: " << data << "\n";
      matchedParens(data);
      return deserializeImpl(data, 0);
    }
protected: 
    TreeNode * deserializeImpl(const string& data, int i) {
      if (i < data.size()-1 && data[i] == '(' && data[i+1]== ')') return NULL;

      size_t j = data.find_first_of(',', i);
      TreeNode * r = new TreeNode(stoi(data.substr(i+1, j-i-1)));
      //skip (
      r->left = deserializeImpl(data, j+1);
      j = parens[j+1];
      r->right = deserializeImpl(data, j+2);
      return r; 
    }

public: 
    vector<int> parens;  //parens[i] is the position of ')' in data string 
 
    vector<string> split(const string& s, char sep) {
      size_t i = 0;
      size_t j = s.find(sep);
      vector<string> ans; 

      while (j != string::npos) {
        ans.push_back(s.substr(i, (j-i)));

        i = j+1; 
        j = s.find_first_of(sep, i);
      }
      return ans; 
    }

    void matchedParens(const string& data) {
        stack<int> sp; 
        int sz = data.size();
        parens = vector<int>(sz, -1);

        for (int i=0; i<sz; ++i) {
          if ('(' == data[i]) sp.push(i);
          else if (')' == data[i]) {
            parens[sp.top()] = i;
            sp.pop();
          }
        }
    }
};

// Your Codec object will be instantiated and called as such:
int main() {
  Codec codec;
  TreeNode * root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->right->right = new TreeNode(4);
  string ss = codec.serialize(root);
  cout << ss << "\n"; 
  codec.matchedParens("(2,(),())");

  TreeNode * p = codec.deserialize(ss);
  cout << "restored tree: "<< "\n";  
  InorderIter it(p);   
  while (it.hasNext()) {
    cout << it.next()->val << " ";
  }
  cout << "\n";
}
