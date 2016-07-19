#include <vector>
#include <queue>
#include <iostream>
using namespace std; 

struct Num {
    int val, idx, p;
    Num(int value, int index, int prime) : val(value), idx(index), p(prime) {}
};

struct Great {
  bool operator()(const Num& n1, const Num& n2) {
      return n1.val > n2.val; 
  }  
};

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size(); 
        priority_queue<Num, vector<Num>, Great> Q; 
        for (int i=0; i<k; ++i) {
            Q.push(Num(primes[i], 1, primes[i]));
        }
        
        vector<int> d(n, 0);
        d[0] = 1;
        for (int i=1; i<n; ++i) {
            d[i] = Q.top().val; 
            cout << "d[" << i << "] = " << d[i] << "\n"; 

            while (d[i] == Q.top().val) {
                Num t = Q.top();
                Q.pop();

                //cout << "pop " << t.val << " " << t.p << "\n"; 
                Q.push(Num(t.p * d[t.idx], t.idx+1, t.p));
            }
            
        }
        return d[n-1];
    }
};
int main() {
  vector<int> primes = {2, 7, 13, 19};
  Solution sol; 
  sol.nthSuperUglyNumber(12, primes); 

}
