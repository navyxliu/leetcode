#include <string>
#include <cctype>
#include <stdio.h>

using namespace std;

class Solution {
    
    void moveRight(const string& s, int &i, int sz) {
        while (++i < sz) {
            if (isalnum(s[i])) break;
        }
    }
    
    void moveLeft(const string& s, int &i) {
        while (--i >= 0) {
            if (isalnum(s[i])) break;
        }
    }
    char myLower(const char c) {
        if (c >= 'A' && c <= 'Z')
            return 'a' + (c - 'A');
        else 
            return c;
    }
public:
    bool isPalindrome(string s) {
        int i = -1; 
        int j = s.size();
        int sz = j; 

        for (int k= 0;k<sz; ++k) {
          printf("%2d", k);
        }
        printf("\n");
        for (int k= 0;k<sz; ++k) {
          printf(" %c", s[k]);
        }
        printf("\n");


        do {
            moveRight(s, i, sz);
            moveLeft(s, j);
            printf("i = %d j = %d\n", i, j);           
            if (i > j || i >= sz || j < 0) break;
            else {
                if (i == j || myLower(s[i]) != myLower(s[j])) 
                    return false; 
            }
        } while(1);
        
        return true; 
    }
};

#include <iostream>
int main() {
  Solution sol;
  printf ("%d\n", sol.isPalindrome("A man, a plan, a canal: Panama"));
}
