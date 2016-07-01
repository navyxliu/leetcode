#include <vector>
#include <utility>
using namespace std; 

typedef pair<int, int> Point;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
      int sz = nums.size();
      vector<int> count(sz, 0);
      vector<Point> points(sz);              
      for (int i=0; i<sz; ++i) {
        points[i] = make_pair(nums[i], i);
      }
      merge_sort(points, 0, sz-1, count); 
      return count; 
    }

    vector<Point> merge_sort(vector<Point>& list, int s, int e, vector<int>& count) {
      int sz = e - s + 1; 
      if (sz <= 0) return vector<Point>();
      else if (sz == 1) return {list[s]};

      vector<Point> list1 = merge_sort(list, s, s+sz/2-1, count);
      vector<Point> list2 = merge_sort(list, s+sz/2, e, count);
      int sz1 = list1.size();
      int sz2 = list2.size();
      int i = 0; int j = 0;
      int inv = 0;
      vector<Point> ans; 

      while (i < sz1 && j < sz2) {
        if (list1[i].first <= list2[j].first) {
          Point p = list1[i++];
          ans.push_back(p);
          count[p.second] += inv;
        }
        else {
          ans.push_back(list2[j++]);
          inv++; 
        }
      }

      while (i < sz1) {
        count[list1[i].second] += inv;
        ans.push_back(list1[i++]);
      }
      while (j < sz2) {
        ans.push_back(list2[j++]); 
      }

      return ans; 
    }
};
#include <iostream>
int main() {
  vector<int> vec = {5,2,6,1};
  Solution sol; 
  auto count = sol.countSmaller(vec);
  for (auto v: count) cout << v << " ";
  cout << "\n";
}
