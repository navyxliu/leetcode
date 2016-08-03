//Problem: Clone Graph
#include <vector>
#include <unordered_map>
using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
    unordered_map<const UndirectedGraphNode *, UndirectedGraphNode *> mem;

public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
      if (node == NULL) return NULL;
      UndirectedGraphNode * ans = new UndirectedGraphNode(node->label);

      mem[node] = ans;
      typedef vector<UndirectedGraphNode*>::const_iterator IT;

      for (IT i = node->neighbors.begin(), e = node->neighbors.end(); i != e; ++i) {
        UndirectedGraphNode * kid;

        if (mem.find(*i) == mem.end()) {
          kid = cloneGraph(*i);
        }
        else {
          kid = mem[*i];
        }

        ans->neighbors.push_back(kid);
      }

      return ans;
    }

};

#include <iostream>
int main() {
  Solution sol;
#if 1
  UndirectedGraphNode n1(1);
  UndirectedGraphNode n2(2);
  UndirectedGraphNode n3(3);
  n1.neighbors.push_back(&n2); 
  n2.neighbors.push_back(&n1); 
  
  n2.neighbors.push_back(&n3); 
  n3.neighbors.push_back(&n2); 
#else
  UndirectedGraphNode n1(0);
  n1.neighbors.push_back(&n1);
  n1.neighbors.push_back(&n1);
#endif

  auto ans = sol.cloneGraph(&n1);
  cout << ans->label << " " << ans << ":\n"; 
  for (auto i : ans->neighbors) {
    cout << i->label << " " << i << " ";  
  }
  cout << endl; 
}
