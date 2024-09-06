#include <vector>
#include <queue>
#include <iostream>
using namespace std; 

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}

    static ListNode * build(const vector<int>& vec) {
      ListNode * h = nullptr; 
      ListNode * p = nullptr; 
 
      for (auto v : vec) {
        if (p == nullptr) {
          h = p = new ListNode(v);
        }
        else {
          p->next = new ListNode(v);
          p = p->next; 
        }
      }

      return h; 
    }
    void print() {
      ListNode * p = this; 

      while(1) {
        printf ("%2d", p->val); 
        p = p->next; 
        if (p != nullptr) printf("->");
        else { 
          printf("\n");
          break;
        }
      } 
    }
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 0 || k == 1 || head == NULL) return head; 
        
        ListNode * p = head; 
        ListNode * q; 
        ListNode * lastQ = NULL;        

        queue<ListNode *> Q; 
        while (q = group(p, k)) {
            ListNode * t = p->next; 
            ListNode * next = q->next; 
            if (p != NULL) { 
              printf("remaining list: ");
              p->print();
              printf("q is %d\n", q->val);
            }
           
            while (t != q->next) {
                Q.push(t);
                t = t->next; 
            }
            
            p->next = q->next; 
            if (lastQ == NULL) {
                head = q; 
            }
            else lastQ->next = q;

            lastQ = p;
            while (!Q.empty()) {
                t = Q.front();
                Q.pop();
                
                t->next = p; //point back 
                p = t; 
            }

            p = next;  
        }
        
        return head; 
    }
    
    ListNode * group(ListNode *p, int k) {
        while (p && --k > 0) {
            p = p->next; 
        }
        
        return p; 
    }
};

int main() {
  Solution sol;
  vector<int> v = {1,2,3,4,5, 6};
  ListNode * h = ListNode::build(v);  
  ListNode * ans = sol.reverseKGroup(h, 3);
  if (ans != NULL) ans->print();  

}
