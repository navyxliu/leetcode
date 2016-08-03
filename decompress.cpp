#include <iostream>
#include <sstream>
#include <string>
using namespace std; 
int findNext(const string& s, int i) {
    int left = 0; 
    int sz = s.size();

    for (int j=i; j<sz; ++j) {
      if (s[j] == ']') {
        if (left == 0) return j; 
        left--; 
      }
      else if (s[j] == '[') left++;
    }
    return -1; 
}

string decompress(const string& s) {
  int rep = 0;
  int sz = s.size();
  int i = 0;
  stringstream ss; 
  string pat; 

  while (i<sz) {
    int ch = s[i++];
    
    if (ch >= '0' && ch <= '9') rep = rep * 10 + ch - '0';
    else if (ch == '[') {
      int j = findNext(s, i);
      pat = decompress(s.substr(i, j-i));
      rep = max(1, rep); 
      i = j+1; 
 
      for (j=0; j<rep; ++j) ss << pat; 
      rep = 0;
    } 
    else {
      rep = max(1, rep);
      for (int j=0; j<rep; ++j) ss << (char)ch; 
      rep = 0;
    }
  }
  return ss.str();
}

int main() {
  cout << decompress("13a2[mtv3[a3[o]v]]a1c[e-e]") << "\n"; 
}
