#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std; 

class FenwickTree {
  vector<int> sum_array;
  int n;
  inline int lowbit(int x) {
    return x & -x;
  }
 
public:
  FenwickTree(int n) :n(n), sum_array(n + 1, 0) {}
 
  void add(int x, int val) {
    while (x <= n) {
      sum_array[x] += val;
      x += lowbit(x);
    }
  }
  
  int sum(int x) {
    int res = 0;
    while (x > 0) {
      res += sum_array[x];
      x -= lowbit(x);
    }
    return res;
  }
};
 
class Solution {
public:
  vector<int> countSmaller(vector<int>& nums) {
    vector<int> temp_num = nums;
    unordered_map<int,int> dic;

    sort(temp_num.begin(), temp_num.end());
    auto end = unique(temp_num.begin(), temp_num.end());
    int k = 0; 
    for (auto i = temp_num.begin(); i != end; ++i) 
      dic[*i] = ++k;
 
    FenwickTree tree(k);
    vector<int> ans(nums.size(),0);
    for (int i = nums.size() - 1; i >= 0; i--) {
      ans[i] = tree.sum(dic[nums[i]] - 1);
      tree.add(dic[nums[i]],1);
    }
    return ans;
  }
};
