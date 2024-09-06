#include <vector>
#include <iostream>
using namespace std;

class DisjointSet {
  vector<int> arr; 
  int sz; 

public:
  DisjointSet() : sz(0) {
    arr.push_back(-1); //exclude 0
  }
  int push() {
    arr.push_back(-1);
    sz++;
    return arr.size()-1; 
  } 

  int root(int x) {
    int i = x; 
    while (arr[i] >= 0) {
      i = arr[i];
    }

    //path compression
    while(arr[x] >= 0) {
      x = arr[x];
      arr[x] = i;
    } 

    return i; 
  }

  void union_(int a, int b) {
    int r1 = root(a);
    int r2 = root(b);
    if (r1 == r2) return;

    if (arr[r1] > arr[r2]) {
      arr[r2] += arr[r1];
      arr[r1] = r2;
    }
    else {
      arr[r1] += arr[r2];
      arr[r2] = r1; 
    }

    sz--;
  }

  int size() const {
    return sz; 
  }
};
class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
      vector<vector<int>> map = vector<vector<int>>(m, vector<int>(n, 0));
      DisjointSet ds;
      vector<int> ans; 

      for (auto & p : positions) ans.push_back(addIsland(p.first, p.second, map, ds, m, n));
      return ans; 
    }

    int addIsland(int x, int y, vector<vector<int>>& map, DisjointSet& ds, int m, int n) {
      if (map[x][y] == 0) {
          vector<int> neigh;
          if (x > 0 && map[x-1][y] != 0) neigh.push_back(map[x-1][y]);
          if (y > 0 && map[x][y-1] != 0) neigh.push_back(map[x][y-1]);
          if (x < m-1 && map[x+1][y] != 0) neigh.push_back(map[x+1][y]);
          if (y < n-1 && map[x][y+1] != 0) neigh.push_back(map[x][y+1]);
          if (neigh.empty()) map[x][y] = ds.push();
          else {
            int i = neigh[0];
            for (int j=1; j<neigh.size(); ++j) {
              ds.union_(i, neigh[j]);
            }
            map[x][y] = ds.root(i); 
          }
      }
      return ds.size();
    }
};
