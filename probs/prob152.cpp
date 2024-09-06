#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        long long neg, pos;
        int sz = nums.size();
        if (sz == 0) return 0;
        if (sz == 1) return nums[0];
        neg = pos = 0;
        long long ans = 0;
        
        for (int i=0; i<sz; ++i) {
            int v = nums[i];

            if (v == 0) neg = pos = 0;
            else if (v > 0) {
                pos = pos == 0 ? v : pos * v;
                neg = neg * v;
            }
            else {
                int t = pos;
                pos = neg * v;
                neg = t == 0 ? v : t * v; 
            }
            //cout << v << " " << pos << " " << neg << "\n";
            ans = max(ans, pos);
        }
        return ans;
    }
};

int main() {
  vector<int> v = {-1, -2, -3, -4, -5};
  Solution sol;

  cout << sol.maxProduct(v);
}
