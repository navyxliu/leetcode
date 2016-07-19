#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std; 

struct Heap {
    int top() const {
        return arr[0];
    }
    
    void pop() {
        swap(arr[0], arr.back());
        arr.pop_back();
        
        siftDown(0);
    }
    
    void push(int x) {
        arr.push_back(x);
        siftUp(arr.size()-1);
    }
protected:
    void siftDown(int i) {
        int sz = arr.size();
        
        while (i*2+1<sz) {
            int kid = i*2+1; 
            
            if (kid<sz-1 && arr[kid+1] < arr[kid])
                kid++;
            if (arr[i]<= arr[kid]) break;
            
            swap(arr[i], arr[kid]);
            i = kid; 
        }
    }
    void siftUp(int i) {
        while (i>0) {
            int p = (i-1)/2;
            
            if (arr[p] <= arr[i]) break;
            swap(arr[p], arr[i]);
            i = p; 
        }
    }
private:
    vector<int> arr;
};
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        Heap heap;
        heap.push(1);
        int i = 1;
        int ans; 
        unordered_set<int> ht;
 
        while (i<=n) {
            ans = heap.top();
            cout << ans <<"\n";

            heap.pop();
            
            for (auto v: primes) {
                int t = v * ans; 
                if (!ht.count(t)) {
                  heap.push(t);
                  ht.insert(t); 
                }
            }
            
            i++;
        }
        return ans; 
    }
};

int main()
{
  vector<int> primes = {2, 7, 13, 19};
  Solution sol; 
  sol.nthSuperUglyNumber(12, primes); 
}
