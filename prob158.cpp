#include <algorithm>
using namespace std; 
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
    char * p; 
    int k {0}; 
    
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int acc = 0;

        while (n>0 && k>0){
            *buf++ = *p++; 
            k--; 
            n--;
            acc++;
        }
        
        while (n >= 4) {
            int c = read4(buf);
            if (c < 4) return acc+c; 
            
            n -= 4;
            acc += 4;
            buf += 4;
        }

        if (n>0) {
            int c = read4(buf);
            acc = acc + min(c, n);
            
            if (n < c) {
                p = buf + n; 
                k = c-n; 
            }
        }
        return acc;
    }
};
