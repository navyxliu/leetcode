#include <vector>
using namespace std;
#if 0
class Solution {
    int detect(const vector<vector<char>>& matrix, int i, int j, int k) {
        int s = 2; 
        
        while (i + s - 1< k && j + s - 1 < k) {
            for (int ii=0; ii<s; ++ii) {
                if (matrix[i+ii][j+s-1] != 1) break;
            }
            for (int jj=0; jj<s; ++jj) {
                if (matrix[i+s-1][j + jj] != 1) break;
            }
            
            s++;
        }
        
        return s-1; 
    }
    
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) return 0;
        
        int n = matrix[0].size();
        int k = min(m, n);
        int ans = 0;
        
        for (int i=0; i<m; ++i) for(int j=0; j<n; ++j) {
            if (matrix[i][j] == 1) {
                ans = max(ans, detect(matrix, i, j, k));        
            }
        }
        
        return ans;
    }
};
#endif
class Solution {
public:
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if (m == 0) return 0;
    int n = matrix[0].size();
    vector<vector<int>> P(m, vector<int>(n, 0));
    int ans = 0;
    
    for (int j=0; j<n; ++j) {
        P[0][j] = matrix[0][j] - '0';
        ans = max(ans, P[0][j]);
    }
    
    for (int i=1; i<m; ++i) {
        P[i][0] = matrix[i][0] - '0';
        ans = max(ans, P[i][0]);
    }
    
    for (int i=1; i<m; ++i) for (int j=1; j<n; ++j) {
        if (matrix[i][j] == '1') {
            P[i][j] = min(P[i-1][j], min(P[i-1][j-1], P[i][j-1])) + 1; 
            ans = max(ans, P[i][j]);
        }
    }
    return ans * ans;; 
}
};
int main() {
  Solution sol;
  //vector<vector<char>> vec = { {1,1}, {1,1}};
  
vector <vector<char>> vec = {
{'1','0','1','0','0'},
{'1','0','1','1','1'},
{'1','1','1','1','1'},
{'1','0','0','1','0'}};
  printf("%d\n", sol.maximalSquare(vec));
}
