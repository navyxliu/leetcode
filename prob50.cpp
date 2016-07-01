#include <iostream>
using namespace std;

class Solution {
public:
    /**
     * @param x the base number
     * @param n the power number
     * @return the result
     */
    double myPow(double x, int n) {
        // Write your code here
        if (n == 0) return 1.0f; 
        if (n == 1) return x; 
        cout << "x, n = " << x << ", " << n; 
        double y = x;
        int i = 1; 

        while (i+i > 0 && i + i <= n) {
            y = y * y; 
            i = i << 1;
            cout << "i " << i << "\n";
        }
         
        return y * myPow(x, n-i);
    }
};
int main() 
{
  Solution sol;
  sol.myPow(0.001, 2147483647);
}
