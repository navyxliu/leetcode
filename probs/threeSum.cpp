#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
  unordered_set<string> mem; 

  bool isSameResult(vector<int>& t, int a, int b) {
    return t[0] == a && t[1] == b;
  }

  string hashIt(int a, int b, int c) {
    return to_string(a) + "," + to_string(b) + "," + to_string(c); 
  } 

  void twoSum(vector<int>& nums, int idx) {
    int target = nums[idx];
    int beg = 0;
    int end = nums.size() - 1;

    while (beg < idx && idx < end) {
      int a = nums[beg];
      int b = nums[end];
      int c = a+b;

      if (c + target == 0) {
        string h = hashIt(a, target, b);

        if (mem.find(h) == mem.end()) {
          mem.insert(h);
        }

        while (1) {
          beg++;
          end--;

          if (beg >= idx || idx <= end || nums[beg] != a || nums[end] != b)
            break;
        }
      }
      else if (c + target < 0)
        beg++;
      else
        end--;
    }
  } 

  vector<int> strToVector(const string& s) {
    vector<int> t(3);
    size_t i = 0;
    size_t j; 

    for (int k=0; k<3; ++k) {
      j = s.find_first_of(',', i);
      t[k] = stoi(s.substr(i, j - i));
      i = j + 1;
    }

    return t; 
  }

  vector<vector<int>> threeSumSlow(vector<int>& nums) {
    int sz = nums.size();
    vector<vector<int>> ans;
    if (sz == 0) return ans;
    
    sort(nums.begin(), nums.end());
    twoSum(nums, 0);
    int prev = nums[0];
    int dup = 1;
    mem.clear();

    for (int i=1; i<sz; ++i) {
      if (prev == nums[i]) dup++;
      else dup = 1;
      
      if (dup <= 2) twoSum(nums, i);
      prev = nums[i];
    }

    for (auto s : mem) {
      ans.push_back(strToVector(s));
    }
    return ans;
  }

  vector<vector<int> > threeSum(vector<int> &num) {
    vector<vector<int> > res;
    std::sort(num.begin(), num.end());
    int sz = nums.size();

    for (int i = 0; i < sz; i++) {
        int target = -num[i];
        int front = i + 1;
        int back = sz-1;

        while (front < back) {
            int sum = num[front] + num[back];

            // Finding answer which start from number num[i]
            if (sum < target)
                front++;

            else if (sum > target)
                back--;

            else {
                vector<int> triplet(3, 0);
                triplet[0] = num[i];
                triplet[1] = num[front];
                triplet[2] = num[back];
                res.push_back(triplet);

                // Processing duplicates of Number 2
                // Rolling the front pointer to the next different number forwards
                while (front < back && num[front] == triplet[1]) front++;

                // Processing duplicates of Number 3
                // Rolling the back pointer to the next different number backwards
                while (front < back && num[back] == triplet[2]) rear--;
            }

        }

        // Processing duplicates of Number 1
        while (i + 1 < sz && num[i + 1] == num[i]) 
            i++;

    }
    return res;
  }  
};
