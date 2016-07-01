#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

struct Value {
    int val; //num
    int n;   //repeat
    Value(int v): val(v), n(1) {}
    Value() : n(0) {}
};

ostream& operator<< (ostream& os, const Value & v){
  os << "(" << v.val << "," << v.n << ")";
  return os; 
}

class Solution {
    unordered_map<int, int> htable; 

public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<Value> heap(nums.size()+1);
        int n = 0;
        
        for (auto v: nums) {
            if (htable.find(v) == htable.end()) {
                Value new_v(v);
                heap[++n] = new_v;
                htable[v] = n;
            }
            else {
                int idx = htable[v];
                Value& old_v = heap[idx];
                cout << "insert v = " << v; 
                cout << old_v << "\n";
                old_v.n++;
                siftUp(heap, idx);
            }
        }

        vector<int> ans; 
        dump(heap, n); 

        while (k-- > 0) {
            swap(heap[1], heap[n]);
            Value v = heap[n--];
            siftDown(heap, 1, n);
            ans.push_back(v.val);

            cout << "ans <- " << v.val << "\n";
            dump(heap, n);
        }
        
        return ans; 
    }
    
    void siftUp(vector<Value>& heap, int i) {
        while (i > 1) {
            int p = i / 2;
            
            if (heap[p].n >= heap[i].n) break;
            
            swap(heap[p], heap[i]);
            htable[heap[p].val] = p;
            htable[heap[i].val] = i;

            i = p; 
        }
    }
    
    void siftDown(vector<Value>& heap, int i, int sz) {
        cout << "before siftDown\n";
        dump(heap, sz);

        do {
            int p = i * 2;

            if (p > sz) break;
            if (p < sz && heap[p+1].n > heap[p].n) {
                p++;    
            }
            
            if (heap[i].n >= heap[p].n) break;
            
            swap(heap[i], heap[p]);
            //don't need to update position. never use them
            i = p; 
        }while (1);
        cout << "after siftDown\n";
        dump(heap, sz);
    }
  
    void dump(vector<Value>& heap, int sz) {
      cout << "dump heap\n";
      for (int i=1; i<=sz; ++i) {
        cout << "(" << heap[i].val << "," << heap[i].n << ")\n";
      } 
    }
/*
    void swap(Value& a, Value& b) {
      cout << "invoke my own swap\n";
      cout << a  << b << "\n"; 

      int t = a.val; 
      a.val = b.val;
      b.val = t;
      t = a.n;
      a.n = b.n;
      b.n = t;

      cout << "after swap:\n";
      cout << "(" << a.val << "," << a.n << ")";
      cout << "(" << b.val << "," << b.n << ")\n";
    }
*/
};

int main()
{
  Solution sol; 
  //vector<int> vec = {1,1,1,2,2,3};
  //vector<int> vec = {5,3,1,1,1,3,73,1};
  vector<int> vec = {-1,1,4,-4,3,5,4,-2,3,-1};
  int n = 3; 

  auto ans = sol.topKFrequent(vec, n); 

  for (auto i : ans) {
    cout << i << " ";
  }
  cout << "\n";
  
}
