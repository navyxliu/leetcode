#include <vector>
#include <iostream>
using namespace std; 

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size()==0) return -1; 
        else if (nums.size()==1) return 0;
        
        return helper(nums, 0, nums.size()-1);
    }
    
    int helper(vector<int>& nums, int lo, int hi){
        int m = lo + (hi-lo)/2;
        int left = m == lo ? INT_MIN : nums[m-1];
        int right = m == hi ? INT_MIN : nums[m+1];
        
        if ( nums[m] > left && nums[m]>right)
            return m;
        else if (left > nums[m])
            return helper(nums, lo, m-1);
        else
            return helper(nums, m+1, hi);
    }
};
int main() {
  Solution sol; 
  vector<int> v = {1,2,3,1};
  cout << sol.findPeakElement(v);
}
