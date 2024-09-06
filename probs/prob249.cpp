#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <iostream>

using namespace std; 

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
      vector<vector<string>>ans;
      map<int, vector<string>> orders;

      for (auto&s : strings) {
        int sz = s.size();
        orders[sz].push_back(s);
      }

      for (auto i : orders) {
        vector<string>& strings2 = i.second; 

        while (strings2.size() > 0) {
          vector<string> g; 
          const string& s = strings2.back();

          strings2.pop_back();
          g.push_back(s);

          for (auto j = strings2.begin(); j!=strings2.end(); ) {
            if (isSame(s, *j)) {
              g.push_back(*j);
              j = strings2.erase(j);
            }
            else j++;
          } 

          ans.push_back(g);
        } 
      }
      return ans;
    }

    bool isSame(const string& s1, const string& s2) {
      int sz1 = s1.size();
      int sz2 = s2.size();
      if (sz1 != sz2) return false;
      if (sz1 == 0) return true; 

      vector<int> dist(sz1);
      for (int i=0; i<sz1; ++i) {
        int ch1 = s1[i]; int ch2 = s2[i];
        dist[i] = ch1 - ch2; 
        if (dist[i] < 0) dist[i] += 26;
      }

      int d = dist[0];
      for (int i=1; i<sz1; ++i) if (dist[i] != d) return false; 
      return true; 
    }
};

int main() {
  Solution sol; 
  cout << boolalpha; 
  cout << sol.isSame("az", "ba") << "\n";
  cout << sol.isSame("az", "ab") << "\n";
  cout << sol.isSame("abc", "xyz") << "\n";
  cout << sol.isSame("abc", "zyx") << "\n";

  vector<string> vec = {"abc", "bab", "zab", "yza", "cba", "acd", "cde", "dcb", "bac", "abd"};
  auto ans = sol.groupStrings(vec);
  for (auto & g: ans) {
    cout << "[";
    for (auto s: g) {
      cout << s << ", ";
    }
    cout  << "]\n";
  }
}
