#include <string>
#include <sstream>
#include <stack>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isAdditiveNumber(string num) {
        int i = 0;
        int sz = num.size();

        bool h = true;
        for (int j=i+1; j<sz; ++j) {
            if (solveIt(i, j, num)) return true;
        }
        
        return false;
    }
    
    bool solveIt(int i, int j, string num) {
        int sz = num.size();
        
        if (sz < 3) return false; 
        if (sz - j * 2 + i < 1) return false;
        if (j - i > 1 && num[i] == '0') return false;
        
        for (int k=j+1; k<sz; ++k) {
            if (num[k] == '0') {
                if (k == sz-1) {
                    for (int t=0; t<sz; ++t) if (num[t] != '0') return false;
                    return true; 
                }
                continue; 
            }
            if (k - j > 1 && num[j] == '0') return false;
            
            string sum = addTwo(i, j, k, num);
            int sz2 = sum.size();
            int kk = 0;
            for (;kk<sz2 && k + kk < sz && num[k+kk] == sum[kk]; ++kk); 
            if (kk == sz2 && (k+kk == sz/*done*/ || solveIt(j, k, num))) return true; 
        }
        
        return false;
    }
    
    string addTwo(int i, int j, int k, const string& num) {
        unsigned long long a = toInt(num.substr(i, j-i));
        unsigned long b = toInt(num.substr(j, k-j));
        
        return toString(a+b);
    }
    
protected:
    unsigned long long toInt(const string& s) {
        int sz = s.size();
        
        unsigned long long  d = 0;
        for (int i=0; i<sz; ++i) {
            d = d * 10 + s[i] - '0';
        }
        
        return d;
    }
    
    string toString(unsigned long long d) {
        stack<int> digits;
        
        while (d > 0) {
            digits.push(d%10);
            d = d / 10;
        }
        
        stringstream ss; 
        while (!digits.empty()) {
            ss << digits.top();
            digits.pop();
        }
        
        return ss.str();
    }
};

int main()
{
  Solution sol;
  //cout << sol.isAdditiveNumber("112358") << "\n";
  cout << sol.isAdditiveNumber("121474836472147483648") << "\n";
}
