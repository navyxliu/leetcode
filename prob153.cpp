#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

class Solution {
public:
#if 0
    int findMin(vector<int>& nums) {
        int lo = 0; 
        int hi = nums.size()-1;
        int last = nums[hi];

        while (lo <= hi) {
            //while (nums[lo] < nums[hi]) break;

            int m = (lo + hi)/2;
            printf ("%d %d %d\n", lo, hi, m);  

            if (nums[m] > last) {
                lo = m+1;
            }
            else 
              hi = m-1;
        }
        printf ("lo = %d\n", lo); 
        return nums[lo];
    }
#endif
  int findMin(vector<int> &num) {
        int start=0,end=num.size()-1;

        while (start<end) {
            if (num[start]<num[end])
                return num[start];

            int mid = (start+end)/2;

            if (num[mid]>=num[start]) {
                start = mid+1;
            } else {
                end = mid;
            }
        }

        return num[start];
    }
};

int main() {
  //vector<int> vec1 = {4,5,6,7,0,1,2};
  //vector<int> vec2 = {2,1};
  vector<int> vec3 = {3,1,2};
  Solution sol; 
  printf(">%d\n", sol.findMin(vec3));
}
