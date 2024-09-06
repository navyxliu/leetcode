#include <vector>
#include <iostream>
using namespace std;

class Solution {
    int bisearch(vector<int>& nums, int lo, int hi, int x) {
        int ans = diff(nums[lo], x);
        int ret = nums[lo];
        cout << "bisearch for " << x << "\n";
        while (lo <= hi) {
            int m = (lo+hi)/2;
            if (diff(nums[m], x) < ans) {
              ret = nums[m];
            } 

            if (nums[m] == x) return x;
            else if (nums[m] < x) lo = m + 1;
            else hi = m - 1 ;
        }
        
        return ret;
    }
    
    int diff(int x, int target) {
        int d = target - x;
        if (d < 0) d = -d;
        return d; 
    }
    
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int lo = 0;
        int hi = nums.size() - 1;
        int ans = INT_MAX;
        int ans2 = -1;
        sort(nums.begin(), nums.end());
        
        while (hi - lo >= 2) {
            int sum = nums[lo] + nums[hi];
            int x = target - sum;
            x = bisearch(nums, lo+1, hi-1, x);
            cout << "(lo, hi) = " << "(" << lo << ", " << hi << ") sum = " << sum << "\n";
            cout << "x = " << x << "\n";
            cout << "diff " << diff(sum+x, target) << " ans " << ans << "\n";
            if (diff(sum+x, target) < ans) {
                ans = diff(sum+x, target);
                ans2 = sum+x;
            }
            
            if (sum+x == target) break;
            else if(sum+x < target) lo++;
            else hi--;
        }
        
        return ans2;
    }
};

int main() {
  Solution sol;
  //vector<int> a = {1,2,4,8,16,32,64,128};
  //int n = 82;
  vector<int> a = {-1, 2,1,-4};
  int n = -1;
  int ans = sol.threeSumClosest(a, n);
  cout <<ans << "\n";
}
