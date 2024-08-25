// prob-416: Partition Equal Subset Sum
//
// Top-down dynamic programming
//
// It is easy to memoize values in Java because all objects are references.
// For a boolean value, each cell has 3 states: null, True, or False.
// For C++ STL containers, it is more convenient to have values rather than indirection.
// The bright side is that it's more compact. This is what Java is pursuing. The downside is that we only have 2 states(true/false).
// We need to leverage std::optional in c++17. it's still a value but gives us 3rd state: nullopt.
//
// Side note:
// This problem is a special case. if computation is true, backtrack terminates immediately with true value.
// Thus, we can use 2 states to memoize recomputation:
// true denotes that we have never seen before; (repurposed here, not memoized computation anymore!)
// false denotes it has been computed and its result is false.
//
#include <vector>
#include <optional>
#include <iostream>
using namespace std;

class Solution {
    // memoization
    vector<vector<optional<bool>>> memo;

    bool backtrack(int idx, int curr, int target, vector<int>& nums) {
        if (curr == target) return true;
        if (idx >= nums.size() || curr > target) return false;

        if (memo[idx][curr].has_value()) {
            return memo[idx][curr].value() == true;
        }

        bool result = backtrack(idx + 1, curr + nums[idx], target, nums) || backtrack(idx + 1, curr, target, nums);
        memo[idx][curr] = result;
        return result;
    }

public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int t : nums) {
            sum += t;
        }
        if (sum % 2 != 0) return false;
        memo = vector<vector<optional<bool>>>(nums.size() + 1, vector<optional<bool>>(sum/2+1, nullopt));
        return backtrack(0, 0, sum/2, nums);
    }
};

int main() {
    cout << boolalpha;

    Solution sol;
    vector<int> in1 = {1,5,11,5};

    cout << sol.canPartition(in1) << endl;
    vector<int> in2 = {1,2,3,5};
    cout << sol.canPartition(in2) << endl;
}