#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std; 

class Solution {
public:
    int countDigitOne(int n) {
        if (n<=0) return 0; 
        
        return digitCounts(1, n);    
    }
    
    unordered_map<int, int> cache; 
    
public:
    /*
     * param k : As description.
     * param n : As description.
     * return: How many k's between 0 and n.
     */
    int digitCounts(int k, int n) {
        if (cache.count(n)) {
            return cache[n];
        }
        
        // write your code here
        if (n < 10) {
            return n>=k ? 1 : 0; 
        }
        else {
            long long x = 10;
            while (x*10 <= n) {
                x *= 10;
            }
            
            int t = n / x;
            int y = x * t; 
            int ans = digitCounts(k, y-1);
            if (t == k) {
                ans += (n - y + 1);
            }
            //cout << "ans " << ans << "\n";
            ans += digitCounts(k, n - y);
            
            cache[n] = ans; 
            
            return ans; 
        }
    }
};

int main() {
  Solution sol; 
  int n = 1410065408;
  cout << sol.countDigitOne(n) << "\n";
}
