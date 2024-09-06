#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std; 

//return an array which values are ranging from 0 to n
vector<int> 
randArray(int n) {
  vector<int> a(n+1);
  for (int i=0; i<=n; ++i) a[i] = i;
  for (int i=0; i<=n; ++i) {
    int j = rand() % (n+1-i);
    swap(a[i], a[j]);
  }
  return a; 
}


int main() {
  srand(time(NULL));
  auto res = randArray(10);

  for (auto v: res) cout << v << " "; 
  cout << "\n";
}
