#include <tuple>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

class Solution {
    unordered_set<string> mem; 

    string toString(const vector<int>& q) {
      stringstream ss; 

      ss << q[0] << ",";
      ss << q[1] << ",";
      ss << q[2] << ",";
      ss << q[3];
      return ss.str();
    } 

    vector<int> strToVector(const string& s) {
      vector<int> t(4);
      size_t i = 0;
      size_t j; 

      for (int k=0; k<4; ++k) {
        j = s.find_first_of(',', i);
        t[k] = stoi(s.substr(i, j - i));
        i = j + 1;
      }

      return t; 
    }

public:
    //O(n^3)
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        mem.clear();
      
        int sz = nums.size(); 
        vector<int> tmp(4);
        int tail; 
        sort(nums.begin(), nums.end());

        for (int i=0; i<sz; ++i) {
          swap(nums[i], nums[sz-1]);
          tail = tmp[0] = nums[sz-1]; 
          nums.pop_back();
          threeSum(nums, target - tail, tmp);
          nums.push_back(tail);
          swap(nums[i], nums[sz-1]);

          // Processing duplicates of Number 1
          while (i + 1 < sz && nums[i + 1] == nums[i]) 
            i++;
        }

        vector<vector<int>> ans;
        for (auto q : mem) {
          ans.push_back(strToVector(q));
        } 
        return ans; 
    }
    
    //only t[0] is unorder. select sort
    void hashValue(vector<int> t) {
      int h = t[0];
      int i; 
      for (i=1; i<=3 && h > t[i] ; ++i) {
        t[i-1] = t[i];
      }

      t[i-1] = h; 
      string s = toString(t);
      cout << "found solution: " << s << "\n";
      mem.insert(s);          
    }

    void threeSum(vector<int> num, int target, vector<int>& quad) {
        int sz = num.size();
        sort(num.begin(), num.end());

        cout << " threeSum: ["; 
        for (int i=0; i<sz; ++i) 
          cout << num[i] << ", "; 
        cout << "] target = " << target << "quad[0] = " << quad[0] << "\n";

        for (int i = 0; i < sz; i++) {
            int x = target - num[i];
            int front = i + 1;
            int back = sz-1;

            while (front < back) {
                int sum = num[front] + num[back];

                // Finding answer which start from number num[i]
                if (sum < x)
                    front++;

                else if (sum > x)
                    back--;
                else {
                    quad[1] = num[i];
                    quad[2] = num[front];
                    quad[3] = num[back];
                    hashValue(quad);

                    // Processing duplicates of Number 2
                    // Rolling the front pointer to the next different number forwards
                    while (front < back && num[front] == quad[2]) front++;

                    // Processing duplicates of Number 3
                    // Rolling the back pointer to the next different number backwards
                    while (front < back && num[back] == quad[3]) back--;
                }

            }

            // Processing duplicates of Number 1
            while (i + 1 < sz && num[i + 1] == num[i]) 
                i++;

        }
    }
};

int main() {
  Solution sol;
  vector<int> v = {1, 0, -1, 0, -2, 2};
  auto ans = sol.fourSum(v, 0);
  for (auto v: ans) {
    cout << "[" << v[0] << ", " << v[1]
      << ", " << v[2] << ", " << v[3] << "]\n";
  }
}
