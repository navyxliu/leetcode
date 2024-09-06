//shortest palindrome
//model: calculate next array for s + "$" + reverse(s)
#include <iostream>
#include <string>
#include <vector>
using namespace std; 

class Solution {
public:
    string shortestPalindrome(string s) {
      if (s.size() <= 1) return s; 
      string rev(s.rbegin(), s.rend()); 
      string str = s + "$" + rev;

      int sz = str.size();
      vector<int> next(sz+1, 0);
      getNext(str, next);

      string ans = rev.substr(0, s.size()- next[sz])  + s;      
      return ans; 
    }

    void getNext(const string& p, vector<int>& next) {
      int sz = p.size(); 
      int j = 0; 
      int k = -1; 
      next[0] = -1;

      while (j < sz) {
        //cout << "j = " << j << " k = " << k << "\n";
        if (k==-1 || p[j] == p[k]) {
          k++; 
          j++;
          next[j] = k;
        }
        else {
          k = next[k];
        }
      }
    }
}; 

int main() {
  Solution sol; 
  cout << sol.shortestPalindrome("abadc")<<"\n";
  cout << sol.shortestPalindrome("abcd") << "\n";
}
