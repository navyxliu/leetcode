#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iterator>
using namespace std; 

class Solution {
  int convert(vector<int>& nums, int base = 10) {
    int d = 0;
    for (auto v : nums)  {
      d = d * base + v; 
    }
    return d; 
  }
public:
  bool doPermutation(vector<int>& nums) {
    int sz = nums.size();
    int i, j, t;
    int prev = convert(nums);

    for (i=sz-2; i>=0 && nums[i] >= nums[i+1]; --i); 
    if (i < 0) return false;
    j = i+1; 
    for (t=i+1; t<sz; ++t) {
      if (nums[t] > nums[i] && nums[t] <= nums[j]) {
        j = t; 
      }
    }
    swap(nums[i], nums[j]);
    reverse(nums, i+1, sz-1);
    if (convert(nums) <= prev)
      throw string("wrong answer!!!");
    return true; 
  } 

  void reverse(vector<int>& nums, int i, int j) {
    while (i < j) {
      swap(nums[i], nums[j]);
      i++; 
      j--;
    }
  }
};

int main()
{
  Solution sol;
#if 0
  vector<int> v = {1,2,3,4,5};
  try {
  do  {
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << "\n";
  }while(sol.doPermutation(v));
  } catch (string e) {
    cout << "caught exception" << e << "\n"; 
    return -1; 
  }
#endif
  vector<int> t = {3,2,1};
  cout << sol.doPermutation(t) << "\n";
  return 0;
}
