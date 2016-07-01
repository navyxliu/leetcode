#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <iostream>

using namespace std; 
class DisjointSet {
  vector<int> arr; 
  int sz; 

public:
  DisjointSet(int n) : sz(n) {
    arr.reserve(n);
    for (int i=0; i<n; ++i) arr[i] = i;
  }
  int root(int x) { int i = x; while (i != arr[i]) i = arr[i]; return i;}
  void merge(int a, int b) {
    int r1 = root(a); int r2 = root(b);
    if (r1 != r2) {
      arr[r2] = r1; 
      sz--; 
    }
  }
};

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
      vector<vector<string>>ans;
      map<int, int> ids; 
      int t = 0; 
      sort(strings.begin(), strings.end(), [](const string&s1, const string& s2) 
        { return s1.size() > s2.size(); });

      DisjointSet ds(strings.size());
      for (int i=0, len=strings.size(); i<len; ++i) {
        const string & s = strings[i];
        int sz = s.size(); 
        int r = ds.root(i);
        if (r != i) continue; 

        for (int j=i+1; j<len && sz == strings[j].size(); ++j) {
          if (j == ds.root(j) && isSame(s, strings[j])) ds.merge(i, j);
        } 
      }

      for (int i=0, len=strings.size(); i<len; ++i) {
        int r = ds.root(i); 
        if (ids.find(r) == ids.end()) {
          ids[r] = t++;
          ans.push_back(vector<string>());
        }
        ans[ids[r]].push_back(strings[i]); 
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
