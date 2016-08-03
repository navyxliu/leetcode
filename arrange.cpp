#include <vector>
#include <iostream>
using namespace std; 

void arrange(vector<int>& a) {
  int i = 0;//even
  int j = 1; //odd
  int sz = a.size(); 
  
  while (i < sz && j < sz) {
    if (a[i] > 0) {
      while (j<sz && a[j] >= 0) {
        j += 2; 
      }

      if (j>= sz) break;

      swap(a[i], a[j]);
      j+=2;
      i+=2;
    }
    else {
      i+=2;
    }
  }
}

void arrange2(vector<int>& a) {
  int i = 0;
      int sz = a.size();
  int j; 

  while (i < sz) {
      if (i % 2) {//odd
        if (a[i] < 0) {//need to change position

            int j = i+1;
      
            while (j<sz && a[j] <= 0) j++; 

            if (j>=sz) break;
            int t = a[i];
            a[i] = a[j];

            while (j>i) {
              a[j] = a[j-1]; 
              j--;
            }         
            a[i+1] = t;
        }
  }
  else {
    if(a[i] > 0) {
    int j = i + 1; 
    while (j<sz && a[j] >= 0) j++; 
    if (j>= sz) break;
    int t= a[i];
    a[i] = a[j];
    while (j>i) {
      a[j] = a[j-1];
      j--;
    } 
    a[i+1] = t;
  }
  }
  
  i++;
  }
}
int main() {
  vector<int> vec = {-5,-2,5,2,4,7,1,8,0,-8};
  arrange2(vec);

  for (auto v: vec) {
    cout << v << " "; 
  }
  cout << "\n";
}
