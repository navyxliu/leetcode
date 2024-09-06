#include <vector>
#include <queue>
#include <iostream>
using namespace std;

#define INF ((1<<31) - 1)
#define CAP(x) (x==INF ? INF : x+1)

class Solution {
    struct Point {
        int x, y, d;
        Point(int i, int j, int dist = 0) : x(i), y(j), d(dist) {}
    };
    
    int m, n; 
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        m = rooms.size(); 
        if (m == 0) return ; 
        n = rooms[0].size();
        for (int i=0; i<m; ++i) for (int j=0; j<n; ++j) if (rooms[i][j] == 0) 
            bfs(i, j, rooms);
    }
    
    void bfs(int x, int y, vector<vector<int>>& rooms) {
        queue<Point> Q;
        Q.push(Point(x, y));
        
        while (!Q.empty()) {
            Point pt = Q.front(); Q.pop();
            rooms[pt.x][pt.y] = pt.d; 
            
            if (pt.x > 0 && check(pt.x-1, pt.y, rooms, pt.d+1))
            {
                Q.push(Point(pt.x-1, pt.y, pt.d+1)); 
                rooms[pt.x-1][pt.y] = -1; 
            }
            if (pt.y > 0 && check(pt.x, pt.y-1, rooms, pt.d+1)) {
                Q.push(Point(pt.x, pt.y-1, pt.d+1));
                rooms[pt.x][pt.y-1] = -1;
            }
            if (pt.x < m-1 && check(pt.x+1, pt.y, rooms, pt.d+1)) {
                Q.push(Point(pt.x+1, pt.y, pt.d+1));
                rooms[pt.x+1][pt.y] = -1;
            }
            if (pt.y < n-1 && check(pt.x, pt.y+1, rooms, pt.d+1)) {
                Q.push(Point(pt.x, pt.y+1, pt.d+1));
                rooms[pt.x][pt.y+1] = -1;
            }
        }
    }
    
    bool check(int x, int y, vector<vector<int>>& rooms, int d) {
        return rooms[x][y] != -1 && rooms[x][y] != 0 && d < rooms[x][y];     
    }
};
int main() {
  Solution sol; 
  vector<vector<int>> rooms; 
//[[2147483647, 0,  2147483647], [ 2147483647, -1,  2147483647]]

  rooms.push_back({2147483647, 0,  2147483647});
  rooms.push_back({2147483647, -1,  2147483647});
  sol.wallsAndGates(rooms);
 
  for (auto & row: rooms) {
    for (auto & v: row) {
      if (v == INF) cout << "INF ";
      else cout << v << " " ; 
    }
    cout << "\n";
  }

 
}
