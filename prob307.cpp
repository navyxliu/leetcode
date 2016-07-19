#include <vector>
#include <iostream>
using namespace std; 
class BIT {
public:
    BIT(int n) {
        sz = n + 1;
        arr = new int[sz];
        //cout << "ctor " << arr << "\n";
        for (int i=0;i<sz; ++i) arr[i] = 0;
    }
#if 0 
    BIT(const BIT& bit) {//copy constructor
        sz = bit.sz; 
        arr = new int[bit.sz];
        for (int i=0; i<sz; ++i) 
            this->arr[i] = bit.arr[i];
    }

    BIT& operator=(const BIT& bit) {//assign
        if (this != &bit) {
            this->sz = bit.sz; 
            delete []arr; 

            this->arr = new int[sz];
            for (int i=0; i<sz; ++i) 
              this->arr[i] = bit.arr[i];
        }
        return *this;
    }
#endif    
    ~BIT() {
        delete []arr; 
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
    int * arr; 
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
void test() 
{
vector<int> nums = {7,2,7,2,0}; 
NumArray a(nums);
a.update(4,6);
a.update(0,2);
a.update(0,9);
a.sumRange(4,4);
a.update(3,8);
a.sumRange(0,4);
a.update(4,1);
a.sumRange(0,3);
a.sumRange(0,4);
a.update(0,4);
}
int main() {
// Your NumArray object will be instantiated and called as such:
vector<int> nums = {1,3,5};
NumArray numArray(nums);
cout << numArray.sumRange(0, 1) << "\n";
numArray.update(1, 10);
cout << numArray.sumRange(1, 2)<< "\n";
test();
}
