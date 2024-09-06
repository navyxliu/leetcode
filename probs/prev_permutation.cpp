#include <vector>
#include <iostream>
using namespace std; 

class Solution {
public:
    /**
     * @param nums: An array of integers
     * @return: An array of integers that's previous permuation
     */
    vector<int> previousPermuation(vector<int> &nums) {
        // write your code here
        int n = nums.size(); 
        if (n <= 1) return nums; 
        int i = n-2; 
        
        for (; i>=0; --i) {
            if (nums[i] > nums[i+1]) 
                break;
        }
        cout << "i " << i << "\n";
        
        if (i>=0) {
            int j = i; 
            for (; j<=n-2; ++j) {
                if (nums[j+1] >= nums[j])
                    break;
            }
            swap(nums[i], nums[j]);
        }
        
        myReverse(nums, i+1, n-1);
        return nums; 
    }
    
    void myReverse(vector<int>& nums, int lo, int hi) {
        while (lo < hi) {
            swap(nums[lo], nums[hi]);
            lo++; 
            hi--;
        }
    }
};
