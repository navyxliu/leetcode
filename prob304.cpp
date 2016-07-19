#include <vector>
#include <iostream>
using namespace std; 

class NumMatrix {
    vector<vector<int>> d; 
    
public:
    NumMatrix(vector<vector<int>> &matrix) {
        int m = matrix.size(); 
        int n = matrix[0].size();
        d = vector<vector<int>>(m, vector<int>(n, 0));
        
        d[0][0] = matrix[0][0];
        for (int i=1; i<m; ++i) {
            d[i][0] = d[i-1][0] + matrix[i][0];
        }
        
        for (int j=1; j<n; ++j) 
            d[0][j] = d[0][j-1] + matrix[0][j];
        
        for (int i=1; i<m; ++i) 
            for (int j=1; j<n; ++j)
                d[i][j] = d[i-1][j] + d[i][j-1] - d[i-1][j-1] + matrix[i][j];
    }
    void dump() {
      for (auto & r: d) {
        for (auto & i : r) cout << i << " ";
        cout << "\n";
      }
      cout <<"\n";
    } 
    int sumRegion(int row1, int col1, int row2, int col2) {
        int val = d[row2][col2]; 
        
        if (row1-1>=0) val -= d[row1-1][col2];
        if (col1-1>=0) val -= d[row2][col1-1];
        if (row1-1>=0 && col1-1>=0) val += d[row1-1][col1-1];
        return val; 
    }
};
int main() {
  vector<vector<int>> matrix = {
  {3, 0, 1, 4, 2},
  {5, 6, 3, 2, 1},
  {1, 2, 0, 1, 5},
  {4, 1, 0, 1, 7},
  {1, 0, 3, 0, 5}
};
  NumMatrix solver(matrix);
  solver.dump(); 
  cout << solver.sumRegion(2, 1, 4, 3) << "\n";
  cout << solver.sumRegion(1, 1, 2, 2) << "\n";
  cout << solver.sumRegion(1, 2, 2, 4) << "\n";
  cout << solver.sumRegion(0, 0, 0, 0) << "\n";
  cout << solver.sumRegion(0, 0, 4, 4) << "\n";
  cout << solver.sumRegion(2, 2, 2, 3) << "\n";
}
