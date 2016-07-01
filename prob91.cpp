#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    int ans;
public:
    int numDecodings(string s) {
        const int n = s.size();
        if (n == 0) return 0; 

        vector<int> w(2*n, 0);

        for (int i=0; i<n; i++) {
          w[i * 2] = s[i] >= '1' && s[i] <= '9' ? 1 : 0;
        }
        if (n == 1) {
          return w[0]; 
        }

        for (int i=0; i<n-1; ++i) {
          w[i*2+1] = w[i*2] * w[i*2+2];

          char tmp[3] = {s[i], s[i+1], 0};
          int t = atoi(tmp);
          if (s[i] != '0' && t >= 1 && t <= 26) {
            w[i*2 + 1]++;
          } 
        }
        w[2*n - 1] = w[2*n-2];

        int pp = w[0];
        int p = w[1];

        for (int i=2; i<n; ++i) {
          int t = pp;
          pp = p;
          p = max(p * w[i*2], t * w[i*2-1]);
        }
        return p;
    }
};

int main() {
  Solution sol;
  cout << sol.numDecodings("12") << "\n";  
  cout << sol.numDecodings("19") << "\n";  
  cout << sol.numDecodings("91") << "\n";  
  cout << sol.numDecodings("121") << "\n";  
  cout << sol.numDecodings("9355141842519423434975558424574331479338913773268525913972842463395324957127519863135646135786662832") << "\n";  
 
}
