#include <vector>
#include <iostream>
using namespace std; 

struct BIT2d {
private: 
  vector<vector<int>> arr; 
  int m, n; 
public: 
  BIT2d() {}

  BIT2d(int sz1, int sz2): m(sz1), n(sz2) {
    arr = vector<vector<int>>(m+1, vector<int>(n+1, 0));
  }

  int sum(int i, int j) {
    int t = 0; 
    i = i + 1; 
    j = j + 1;

    while (i>0) {
        int jj = j; 
        while (jj > 0) {
          t += arr[i][jj];
          jj -= jj&(-jj);
        }
        i -= i & (-i);
    }

    return t; 
  }

  void update(int i, int j, int d) {
    i = i + 1; 
    j = j + 1; 

    while (i<=m) {
      int jj = j; 

      while (jj<=n) {
        arr[i][jj] += d; 
        jj += jj&(-jj);        
      }

      i += i&(-i);
    } 
  }
  
  int cell(int i, int j) {
    int val = sum(i, j);
    val -= sum(i-1, j) + sum(i, j-1);
    val += sum(i-1, j-1);
    return val; 
  }
};

class NumMatrix {
    BIT2d bit; 
    int m, n; 
public:
    NumMatrix(vector<vector<int>> &matrix) {
      m = matrix.size();
      if (m == 0) return; 
      n = matrix[0].size();
      if (n == 0) return;
      
      bit = BIT2d(m, n);
      for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) bit.update(i, j, matrix[i][j]);
    }

    void dump() {
      for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) 
          cout << bit.cell(i, j) << " ";
        cout << "\n";
      } 
      cout << "\n";
    }

    void update(int row, int col, int val) {
      int old = bit.cell(row, col);    
      bit.update(row, col, val-old);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
      int val = bit.sum(row2, col2);
      val -= bit.sum(row1-1, col2) + bit.sum(row2, col1-1);
      val += bit.sum(row1-1, col1-1);
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
// Your NumMatrix object will be instantiated and called as such:
NumMatrix numMatrix(matrix);
numMatrix.dump();
cout << numMatrix.sumRegion(2, 1, 4, 3) << "\n";
numMatrix.update(3, 2, 2);
cout << numMatrix.sumRegion(2, 1, 4, 3) << "\n";
}
