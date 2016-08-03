#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std; 

struct Node {
    int freq {0}; 
    int idx {-1};
};
//minheap
struct Heap {
    vector<int> arr; 
    unordered_map<int, Node>&  ht; 
    
public: 
    Heap(unordered_map<int, Node>& htable) : ht(htable) {}
    
    void push(int val) {
        arr.push_back(val);
        int i = arr.size()-1; 
        ht[val].idx = i;
        
        siftUp(i);
    }
    int size() const {
        return arr.size(); 
    }
    
    void incr(int idx) {
        siftDown(idx);
    }
    
    int top() const {
        return arr[0];
    }
    
    void pop() {
        int i = arr.size()-1; 
        
        swap(arr[0], arr[i]);
        ht[arr[0]].idx = 0;
        ht[arr[i]].idx = -1;
        
        arr.pop_back();
        
        siftDown(0);
    }
    
protected: 
    void siftUp(int i) {
        int sz = arr.size();
        
        while (i>0) {
            int p = (i-1)/2; 
            
            if (ht[arr[p]].freq <= ht[arr[i]].freq)
                break;
                
            swap(arr[p], arr[i]);
            swap(ht[arr[p]].idx, ht[arr[i]].idx);
            i = p;     
        }
    }
    
    void siftDown(int i) {
        int sz = arr.size();
        
        while (i*2+1<sz) {
            int p = 2*i+1;
            
            if (p < sz-1 && ht[arr[p+1]].freq < ht[arr[p]].freq)
                p++;
                
            if (ht[arr[i]].freq <= ht[arr[p]].freq) 
                break;
            
            swap(arr[i], arr[p]);
            swap(ht[arr[i]].idx, ht[arr[p]].idx);
            i = p ;
        } 
    }
public:
    void dump() {
      cout << "["; 
      for (auto i : arr) cout << i << "(" << ht[i].freq << ")" << ", ";
      cout << "]\n";
    }
};


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, Node> ht; 
        Heap pq(ht); 
        
        for (auto v: nums) {
            cout << v << "\n"; 

            Node & node = ht[v];
            node.freq++;
            
            if(node.idx != -1) {
                pq.incr(node.idx);
            }
            else if (pq.size() < k) {
                pq.push(v);
            }
            else if (node.freq > ht[pq.top()].freq) {
                pq.pop();
                pq.push(v);
            }
            pq.dump();  
        }
        
        vector<int> ans(k);
        for (int i=k-1; i>=0; --i) {
            ans[i] = pq.top(); 
            pq.pop(); 
        }
        return ans; 
    }
};

int main() {
  vector<int> v = {5,-3,9,1,7,7,9,10,2,2,10,10,3,-1,3,7,-9,-1,3,3};
  int k = 3;
  Solution sol; 
  auto output = sol.topKFrequent(v, k);
  for (auto l : output) cout << l << " "; 
  cout << "\n";
}
