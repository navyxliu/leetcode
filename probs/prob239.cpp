#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> mq; // monotonic queue. element is the index

        for (int i = 0; i < k; ++i) {
            while (!mq.empty() && nums[i] >= nums[mq.back()]) {
                mq.pop_back();
            }
            mq.push_back(i);
        }
        vector<int> res;
        res.push_back(nums[mq.front()]);

        for (int i=k; i < nums.size(); ++i) {
            while (!mq.empty() &&  nums[i] >= nums[mq.back()]) {
                mq.pop_back();
            }
            mq.push_back(i);

            // delete the deprecated indices
            while (mq.front() <= i - k) {
                mq.pop_front();
            }
            res.push_back(nums[mq.front()]);
        }

        return res;
    }
};

//Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
//Output: [3,3,5,5,6,7]
int main() {
    Solution solution;
    vector<int> input = {1,3,-1,-3,5,3,6,7};
    int k = 3;
    vector<int> ans = solution.maxSlidingWindow(input, k);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
