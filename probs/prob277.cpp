#include <vector>
using namespace std; 

// Forward declaration of the knows API.
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        vector<vector<int>> G(n, vector<int>(n, INT_MAX));
        vector<int> color(n, 1);
        
        while (1) {
            int a = -1; 
            int b = -1; 
            int i; 
            for (i=0; i<n; ++i) if (color[i] == 1) {
                if (a == -1) {
                    a = i; 
                }
                else if (b == -1) {
                    b = i; 
                    break; 
                }
            }
            
            if (a == -1) return -1;
            else if (b == -1) {
                if (verify(a, n, G)) return a;
                else return -1;
            }   
            
            bool r = knows(a, b);
            if (r) {
                color[a] = 0;
                G[a][b] = 1;
            }
            else {
                color[b] = 0;
                G[a][b] = 0;
            }
        }
        return -1;
    }
    
    bool verify(int a, int n, vector<vector<int>>& G) {
        for (int i=0; i<n; ++i) {
            if (i == a) continue; 
            
            if (G[i][a] != INT_MAX) {
                if (G[i][a] != 1) return false; 
            }
            else {
                G[i][a] = knows(i, a) ? 1 : 0;
                if (G[i][a] != 1) return false;             
            }
            
            
            if (G[a][i] != INT_MAX) {
                if (G[a][i] != 0) return false;
            }
            else {
                G[a][i] = knows(a, i) ? 1 : 0;
                if (G[a][i] != 0) return false; 
            }
        }
        
        return true; 
    }
};
