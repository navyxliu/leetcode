#include <vector>
#include <iostream>
using namespace std;

class BIT {
public:
    BIT(int n) {
        sz = n + 1;
        arr = vector<int>(sz, 0);
    }
    
    int sum(int i) {
        int t = 0;
        i = i + 1;
        
        while (i>0) {
            t += arr[i];
            i -= i & (-i);
        }
        
        return t; 
    }
    
    int readSingle(int idx) {
        idx = idx+1;
        int sum = arr[idx];
        if (idx > 1){ // special case
            int z = idx - (idx & -idx); // make z first
            idx--; // idx is no important any more, so instead y, you can use idx
            while (idx != z){ // at some iteration idx (y) will become z
                sum -= arr[idx];
                idx -= (idx & -idx);
            }
        }
        return sum;
    }
    
    void update(int i, int d) {
        i = i + 1;
        
        while (i < sz) {
            arr[i] += d; 
            i += i & (-i);
        } 
    }
    
private:
    vector<int> arr; 
    int sz; 
};

class NumArray {
    BIT bit; 
    
public:
    NumArray(vector<int> &nums): bit(nums.size()) {
        int sz = nums.size();

        for (int i=0; i<sz; ++i) 
          bit.update(i, nums[i]);
    }

    void update(int i, int val) {
      int old = bit.readSingle(i);    
      bit.update(i, val-old);
    }

    int sumRange(int i, int j) {
      if (i > j) swap(i, j); 
      return bit.sum(j) - bit.sum(i-1);
    }
};

int main() 
{
vector<int> nums = {7,2,7,2,0}; 
NumArray a(nums);

a.update(4,6);
a.update(0,2);
a.update(0,9);
cout << a.sumRange(4,4) << "\n";
a.update(3,8);
cout << a.sumRange(0,4) << "\n";
a.update(4,1);
cout << a.sumRange(0,3) << "\n";
cout << a.sumRange(0,4) << "\n";
a.update(0,4);
}

