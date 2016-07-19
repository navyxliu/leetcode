#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std; 

class Solution {
  unordered_map<int, bool> cache; 

public:
    bool isMatch(string s, string p) {
        int n = s.size();
        
        int m = p.size();
        if (m > 0) {
            vector<char> r;
            r.push_back(p[0]);
            
            for (int i=1; i<m; ++i) {
                if (r.back() == '*' && p[i] == '*')
                    continue; 
                else 
                    r.push_back(p[i]);
            }    
            p = string(r.begin(), r.end());
            m = p.size();
            cout << "new p " << p << "\n"; 
        }
        return helper(s, p, 0, 0, n, m);
    }
    
    bool helper(const string& s, const string& p, int i, int j, int n, int m) {
        if (i >= n) {
            while (j<m) {
                if (p[j] != '*') return false; 
                j++;
            }
            return true; 
        }
        
        if (j >= m) {//i<n
            return false; 
        }
        int key = (i<<16)|j;
        if (cache.count(key)) return cache[key];

        if (p[j] == '?' || s[i] == p[j]) {
            return cache[key] = helper(s, p, i+1, j+1, n, m);
        }
        else if (p[j] == '*') {
          int jj = j+1; 

          while (jj<m) {
            if (p[jj] == '*' || p[jj] == '?') break;
            jj++;
          }
          int len = jj - j - 1; 
          if (len == 0) return true; 

          string sub = p.substr(j+1, len);
          //cout << "after *, match sub = " << sub << "\n";
          size_t ii;

          while (i < n) { 
            //cout << "s.find i " << i << " sub =" << sub << "\n";
            ii = s.find(sub, i);

            if (ii  == string::npos) break;

            //cout << "find in ii = " << ii << " s: " << s.substr(ii, len) << "\n"; 

            if (helper(s, p, ii + len, jj, n, m)) 
              return true; 

            i = ii + 1; 
          }
        }

        cache[key] = false;  
        return false; 
    }
};

int main() 
{
  Solution sol; 

  string s = "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb";
  string p = "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb";
  cout << sol.isMatch(s, p);
#if 0
  int n = s.size();
  int i = 0;
  int ii; 
  string sub = "bbabb";
  int len = sub.size();

  while (i<n && ((ii=s.find(sub, i)) != string::npos)) {
    cout << "find in ii = " << ii << " s: " << s.substr(ii, len) << "\n"; 
    i = ii + 1;
    cout << "i = " << i << "\n";
  }
#endif
}
