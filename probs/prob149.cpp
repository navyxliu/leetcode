struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(vector<Point>& points) {
      int sz = points.size();
      unordered_map<double, int> ht; 
      if (sz < 3) return sz; 

      int ans = 1; 

      for (int i=0; i<sz; ++i) {
        ht.clear();
        Point& p1 = points[i];
        int dup = 1; 

        for (int j=0; j<sz; ++j) {
          if (i == j) continue; 

          Point& p2 = points[j];
          if (p1.x == p2.x && p1.y == p2.y) dup++;
          else {
            double slope = 0.0f;
            if (p1.x == p2.x) slope = INT_MAX; 
            else {
              slope = (p2.y - p1.y) / (p2.x - p1.x);
            }
            ht[slope]++;
          }           
        }
        if (ht.size() == 0) {
          ans = max(ans, dup);
        }
        else {
          for (auto p : ht) {
            ans = max(ans, dup + p.second);
          }
        }
      }       

      return ans; 
    }
};
