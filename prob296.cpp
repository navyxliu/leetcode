#include <vector>
#include <algorithm>
using namespace std; 

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
      int m = grid.size();
      int n = grid[0].size();
      vector<int> I; 
      vector<int> J;
      for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) 
        if (grid[i][j] == 1) { I.push_back(i); J.push_back(j); }

      return getMin(I) + getMin(J);
    }

    int getMin(vector<int>& list) {
      sort(list.begin(), list.end());

      int i = 0; 
      int j = list.size()-1;
      int ans = 0;
      while (i < j) {
        ans += list[j--] - list[i++];
      }
      return ans; 
    }
};
