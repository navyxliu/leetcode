#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;
#if 0
class ValidWordAbbr {
    vector<string> dict; 
    
public:
    ValidWordAbbr(vector<string> &dictionary) {
        dict = dictionary; 
        sort(dict.begin(), dict.end(), [](const string& a, const string & b) {
          return abbr(a) < abbr(b);    
        });

        auto it = unique(dict.begin(), dict.end());
        dict.erase(it, dict.end());

        for (auto & s: dict) {
          cout << s << "\n";
        }
    }

    bool isUnique(string word) {
      int lo = 0;
      int hi = dict.size()-1; 
      string sub = abbr(word);

      while (lo <= hi) {
        int m = ( lo + hi ) /2;
        string t = abbr(dict[m]); 
        if (t == sub) return check(m, word, sub);
        else if (t > sub) hi = m - 1; 
        else lo = m + 1;
      }
     
      return true;
    }
    
private: 
    bool check(int m, const string & s, const string& sub) {
      cout << "checking " << dict[m] << " s = " << s << " sub " << sub << "\n";
      if (dict[m] != s) return false;

      if (m > 0 && abbr(dict[m-1]) == sub) 
        return false;

      int sz = dict.size();
      if (m < sz-1 && abbr(dict[m+1]) == sub) 
        return false;
      return true; 
    }

    static string abbr(const string& s) {
        int sz = s.size();
        if (sz <= 2) return s; 
        return s[0] + to_string(sz-2) + s[sz-1];
    }
};
#endif
class ValidWordAbbr {
    map<string, vector<string>> mem; 
    
public:
    ValidWordAbbr(vector<string> &dictionary) {
        for (auto & s : dictionary) {
            string sub = abbr(s);
            bool skip = false;
            
            if (mem.find(sub) != mem.end()) {
                const vector<string>& mapped = mem[sub];
                skip = mapped.end() != find(mapped.begin(), mapped.end(), s);
            }
            
            if (!skip) mem[sub].push_back(s);            
        }
    }
    
    bool isUnique(string word) {
      string sub = abbr(word);
      if (mem.find(sub) == mem.end()) return true; 
      
      const vector<string>& results = mem[sub];
      if (results.size() == 1 && results[0] == word) return true; 
      
      return false;
    }
    
private: 
    static string abbr(const string& s) {
        int sz = s.size();
        if (sz <= 2) return s; 
        return s[0] + to_string(sz-2) + s[sz-1];
    }
};

// Your ValidWordAbbr object will be instantiated and called as such:
// ValidWordAbbr vwa(dictionary);
// vwa.isUnique("hello");
// vwa.isUnique("anotherWord");

int main() {
  vector<string> dict = { "deer", "door", "cake", "card" };
  ValidWordAbbr vwa(dict);

  cout << boolalpha; 
  cout << vwa.isUnique("dear") << "\n";
  cout << vwa.isUnique("cart") << "\n";
  cout << vwa.isUnique("cane") << "\n";
  cout << vwa.isUnique("make") << "\n";
  cout << "==============================\n";

  vector<string> dict2 = { "hello"};
  ValidWordAbbr vwa2(dict2);
  cout << vwa2.isUnique("hello") << "\n";
  cout << vwa2.isUnique("heelo") << "\n";
  cout << vwa2.isUnique("sweet") << "\n";
  cout << "==============================\n";

  vector<string> dict3 = { "a", "a", "a"};
  ValidWordAbbr vwa3(dict3);
  cout << vwa3.isUnique("a") << "\n";
 
  return 0;
}
