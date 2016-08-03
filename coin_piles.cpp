#include <iostream>
#include <vector>
using namespace std; 

int solve(vector<vector<int>>& coins, int n) {
  int m = coins.size();
  if (m == 0 || n == 0) return 0;

  vector<vector<int>> d(m, vector<int>(n+1, 0));
  int S = 0;
  d[0][0] = 0;
  for (int i=1; i<=n; ++i) {
    if (i-1 < coins[0].size()) 
      S += coins[0][i-1];

    d[0][i] = S;
  }

  for (int i=1; i<m; ++i) {
    for (int j=0; j<=n; ++j) {
      int t = d[i-1][j];
      int s = 0;

      for (int k=1; k<=j; ++k) {
        if (k-1 < coins[i].size()) 
          s += coins[i][k-1];       
        if (d[i-1][j-k] + s > t) 
          t = d[i-1][j-k] + s;
      }

      d[i][j] = t; 
    }
  }

  return d[m-1][n];
}

int main() {
  vector<vector<int>> coins = {{1,2}, {3}};
  cout << solve(coins, 1) << "\n";
  cout << solve(coins, 2) << "\n";
  cout << solve(coins, 3) << "\n";
  cout << solve(coins, 4) << "\n";

  cout << "second case\n";
  coins = {{2,2,1}, {3}, {1,4,4}};
  cout << solve(coins, 1) << "\n";
  cout << solve(coins, 2) << "\n";
  cout << solve(coins, 3) << "\n";
  cout << solve(coins, 4) << "\n";

 
}
