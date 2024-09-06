#include <iostream>
using namespace std; 
int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (b == 0) return a; 
  else return gcd(b, a%b); 
}

int gcd_ex(int a, int b, int& x, int & y) {
  if (b == 0) {
    x = 1; 
    y = 0;
    return a; 
  }
  else {
    int res = gcd_ex(b, a%b, x, y);
    //x = y1
    //y = x1 - (a/b)*y1
    int t = x; 
    x = y;
    y = t - (a/b)*y;
    return res;
  }
}

int main() {
  cout << gcd(6, 9) << "\n";
  cout << gcd(9, 6) << "\n";
  cout << gcd(34, 5) << "\n";

  int x, y; 
  cout << gcd_ex(9, 6, x, y);
  cout << " " << x << " " << y << "\n";

  cout << gcd_ex(34, 1, x, y);
  cout << " " << x << " " << y << "\n";

}
