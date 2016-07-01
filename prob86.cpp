#include <stdio.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    ListNode * merge(ListNode * less, ListNode * less_p, ListNode * after, ListNode * after_p) {
      if (after_p != NULL) after_p->next = NULL;
      if (less_p == NULL) return after;

      less_p->next = after;
      return less; 
    }

public:
    ListNode* partition(ListNode* head, int x) {
      ListNode * less = NULL;
      ListNode * greater = NULL; 
      ListNode * less_p = NULL, * greater_p = NULL; 
      

      ListNode * p = head;
      while (p) {
        if (p->val < x) {
          if (less == NULL) {
            less_p = less = p;
          }
          else
          {
            less_p->next = p; 
            less_p = p;
          }
        }
        else {
          if (greater == NULL) {
            greater_p = greater = p;
          }
          else
          {
            greater_p->next = p; 
            greater_p = p;
          }
        }

        p = p->next;
      }

      return merge(less, less_p, greater, greater_p);
    }
};
#include <iostream>
using namespace std;

int main() {

  ListNode * l = new ListNode(1);
  l->next = new ListNode(4);
  l->next->next = new ListNode(3);
  l->next->next->next = new ListNode(2);
  l->next->next->next->next = new ListNode(5);
  l->next->next->next->next->next = new ListNode(2);

  Solution sol;
  ListNode * ans = sol.partition(l, 3);
  while (ans) {
    cout << ans->val << " "; 
    ans = ans->next;
  }
}
