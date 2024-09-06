#include <vector>
#include <unordered_map>
using namespace std; 

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
      unordered_map<int, int> d; 
      int w = t+1;
      int sz = nums.size(); 

      for (int i=0; i<sz; ++i) {
        int m = nums[i]/w; 
        if (d.find(m) != d.end()) return true; 
        if (d.find(m-1) != d.end() && test(nums[i], m-1, t))
          return true; 
        if (d.find(m+1) != d.end() && test(nums[i], m+1, t))
          return true; 

        d[m] = nums[i];
        if (i >= k) d.erase(nums[i-k]/w);
      }       
      return false; 
    }


    bool test(int a, int b, int t) {
      int i = a - b < 0 ? b - a : a-b;
      if (i < 0) return false;
      return i <= t; 
    }
};
