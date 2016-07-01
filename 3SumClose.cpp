#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std; 

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        unordered_set<long long> mem; 
        
        for (int i=0; i<n; ++i) for (int j=i+1; j<n; ++j) {
            int t = bisearch(nums, target - nums[i]- nums[j], j+1, n-1);
            long long s = i;
            s = (s<<20) | j; 
            s <<= 20;
            for (int k=j+1; k<t; ++k) {
                mem.insert(s|k);
            }
        }
        return mem.size();
    }
    
    int bisearch(vector<int>& nums, int target, int lo, int hi) {
        while (lo <= hi) {
            int m = (lo+hi)/2;
            if (nums[m] < target)
                lo = m+1;
            else
                hi = m-1;
        }
        return lo; 
    }
};
int main() {
  //vector<int> vec = {14,-11,6,-4,-10,-11,-3,3,2,-10,-15,10,-2,5,-11,-7,-1,11,-4,5,7,5,-7,-14,-15,-8,2,5,-2,-2,-15,5,4,13,-7,12,-3,7,14,-5,-9,-5,-6,-13,-5,1,-10,-10,-3,-5,7,14,2,-7,-1,-6,-1,-3,-7,-12,0,0,-2,8,-9,12,-3,-3,-15,-9,-15,-7,-11,14,-14,-7,-4,-1,-8,-3,4,8,2,3,9,-1,13,-2,11,8,3,-2,3,-10,10,-2,-5,-12,-10,-3,5,14,1,3,11,3,-13,7};
  vector<int> vec = {3,8,11,0,0,-2,9,7,-10,5,4,-8,0,-8,10,2,12,-7,5,-5,6,-2,13,4,-14,6,8,-2,-14,2,7,-4,-8,8,1,-7,-1,11,11,-8,-5,-6,10,-2,2,-14,-4,-1,11,-15,-10,12,-5,-13,1,-11,-8,-4,-5,-5,-14,-6,-15,7,10,-9,0,7,-13,3,-9,11,-10,-10,-10,12,4,7,-6,-12,5,-4,11,-6,4,4,-7,-12,-6,-7,7,3,7,6,0,2,-9,-7,-12,9,-15,-8,-2,-14,10,-1,-9,-15,-14,-12,10,14,-13,-5,10,14,11,11,3,-1,14,3,-7,0,-9,-7,7,9};
  int target = 22;
  cout << "size = " << vec.size() << "\n";
  Solution sol; 
  cout << sol.threeSumSmaller(vec, target) << "\n";
}
