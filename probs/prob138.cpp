#include <unordered_map>
using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode * p, * newhead; 
        p = newhead = NULL;
        RandomListNode * t = head; 
        unordered_map<RandomListNode *, RandomListNode *> map; 
        
        while (t) {
            RandomListNode * n = new RandomListNode(t->label);
            n->random = t; 
            map[t] = n; 
            
            if (p != NULL) {
                p->next = n; 
                p = n;
            }
            
            if (!newhead) {p = newhead = n;}
            t = t->next; 
        }
        
        t = newhead; 
        while (t) {
            RandomListNode * o = t->random; 
            if (!o->random) t->random = NULL;
            else t->random = map[o->random];
            t = t->next; 
        }
        
        return newhead; 
    }
};
