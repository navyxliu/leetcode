#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lis(const vector<int> & seq) {
    int sz = seq.size();
    
    //L[i] = 1 + L[j]  if j < i and arr[j] < arr[i]
    vector<int> L(sz);
    
    for (int i=0; i<sz; ++i) L[i] = 1;
    
    for(int i=1; i<sz; ++i) 
        for (int j=0; j<i; ++j) 
            if (seq[j] < seq[i]) 
                L[i] = max(L[i], L[j] + 1);
    
    int m = 0;
    for (int i=0; i<sz; ++i) if(L[i] > m) m = L[i]; 
    return m;
}

int main() {
    int t; cin >> t;
    
    while (t > 0) {
        int n, a; 
        vector<int> seq;
        cin >> n; 
        for (int i=0; i<n; ++i) {
            cin >> a;
            seq.push_back(a);
        }
        cout << lis(seq) << "\n";
        t--;
    }
}
