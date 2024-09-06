#include <vector>
#include <iostream>
using namespace std; 

class Solution {
public:
    /**
     * @param m: An integer m denotes the size of a backpack
     * @param A: Given n items with size A[i]
     * @return: The maximum size
     */
    int backPack(int m, vector<int> A) {
        // write your code here
        int n = A.size(); 
        //int sum = 0;
       // for (int i=0; i<n; ++i) sum += A[i];
        vector<bool> d(m+1, false);
        d[0] = true; 
        
        for (int i=0; i<n; ++i) {
            for (int j=m-A[i]; j>=0; --j) 
                if (d[j] && j + A[i] <= m){
                    d[j+A[i]] = true;
                    cout << "j + A[i]" << j + A[i] << "\n";
                }
        }
        
        for (int j=m; j>=0; j--) {
            cout << "j = " << j << " " << d[j] << "\n";
        }
        while (m>0 && !d[m])
            m--; 
            
        return m; 
    }
};

int main() {
  vector<int> v = {3,4,8,5};
  int m = 10;
  Solution sol; 
  cout << sol.backPack(m, v);
}
