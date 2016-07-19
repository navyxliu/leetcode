#include <string>
#include <unordered_map>
#include <iostream>
using namespace std; 

class Solution {
public:
    string minWindow(string s, string t) {
        int i = 0; int j = 0;
        int sofar = INT_MAX;
        string ans; 
        unordered_map<char, int> tset;
        unordered_map<char, int> win; 
        
        for (auto ch : t) tset[ch]++;
        unordered_map<char, int> tset2; 
        tset2 = tset; 
 
        int sz2 = t.size();
        int sz1 = s.size();
        
        while (j<sz1) {
            char ch = s[j++];
            win[ch]++;

            if (tset.find(ch) != tset.end()) {
              remove(tset, ch);              

              while (tset.empty()) {
                if (j-i < sofar) {
                  sofar = j-i;
                  ans = s.substr(i, sofar);
                }
                ch = s[i++];
                remove(win, ch);

                if (tset2.find(ch) != tset2.end() && tset2[ch] > win[ch])
                  tset[ch]++;  
              }
            }
        }
        
        return ans;
    }
    
    bool cover(unordered_map<char, int>& win, unordered_map<char, int>& tset) {
        for (auto it: tset) if (win.find(it.first) == win.end() || win[it.first] < it.second) return false; 
        return true; 
    }

    void remove(unordered_map<char, int>& dic, char ch) {
      dic[ch]--;
      if (dic[ch] == 0) dic.erase(ch);
    }
};

int main() {
  Solution sol; 
  string s = "aa";
  string t = "aa";
  cout << sol.minWindow(s, t) << "\n";
}
