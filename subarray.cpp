#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std; 

class Solution {
struct MyNode {
    int val; 
    int idx; 
    MyNode(int value, int index) : val(value), idx(index) {}

    bool operator<(const MyNode & s) const {
        return (val < s.al) || (val == s.val && idx < s.idx); 
    }
};
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    vector<int> subarraySumClosest(vector<int> nums){
        // write your code here
        vector<MyNode> prefix;
        int sum = 0;
        int sz = nums.size(); 
        
        for (int i=0; i<sz; ++i) {
            sum += nums[i];
            prefix.emplace_back(sum, i);
        }
        sort(prefix.begin(), prefix.end());
        
        int diff = INT_MAX; 
        int lo, hi;
        
        for (int i=1; i<sz; ++i) {
            if ((prefix[i].val - prefix[i-1].val) < diff) {
                diff = prefix[i].val - prefix[i-1].val;
                lo = min(prefix[i].idx, prefix[i-1].idx) + 1; 
                hi = max(prefix[i].idx, prefix[i-1].idx);
            }        
        }
        
        return {lo,hi};
    }
};

