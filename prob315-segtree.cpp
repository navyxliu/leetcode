#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std; 

class SegTree {
public:
  SegTree(int n) {
    sz = calSize(n)* 2-1;
    this->n = n; 
    tree = new int[sz];
    for (int i=0; i<sz; ++i) tree[i] = 0;
  }

  int query(int qlo, int qhi) {
    return doQuery(qlo, qhi, 0, n-1, 0);
  }

  void update(int qlo, int qhi, int val) {
    doUpdate(qlo, qhi, 0, n-1, val, 0);
  }

protected:
  int doQuery(int qlo, int qhi, int lo, int hi, int pos) {
    if (lo > hi) return 0; 

    if (qlo <= lo && qhi >= hi) //totally overlap
      return tree[pos];      

    if (qhi < lo || qlo > hi) //no overlap
      return 0;

    int m = (lo+hi)/2;
    return doQuery(qlo, qhi, lo, m, pos*2+1) + doQuery(qlo, qhi, m+1, hi, pos*2+2);
  }

  void doUpdate(int qlo, int qhi, int lo, int hi, int val, int pos) {
    if (lo > hi) return ;
    if (qlo > hi || qhi < lo) return ;

    if (qlo <= lo && qhi >= hi) {
      tree[pos] += val; 
      return; 
    }
    int m = (lo+hi)/2;
    doUpdate(qlo, qhi, lo, m, val, pos*2+1);
    doUpdate(qlo, qhi, m+1, hi, val, pos*2+2); 
    tree[pos] = tree[pos*2+1] + tree[pos*2+2];
  }

private: 
  int * tree; 
  int sz, n; 

  bool isPower2(int x) {
    return 0 == (x&(x-1));
  }

  int calSize(int x) {
    int i = 1; 
    while (i<x) {
      i<<=1;  
    }
    return i; 
  }

public:
  void dump() {
    for (int i=0; i<sz; ++i) 
      cout << tree[i] << " " ; 
    cout << "\n";
  }
  
};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
      unordered_map<int, int> dic; 
      vector<int> tmp = nums; 
      int sz = nums.size(); 
      sort(tmp.begin(), tmp.end());
      int k=0; 
      for (auto i=tmp.begin(),e=tmp.end();  i!= e; ++i) {
        dic[*i] = ++k;
      }

      SegTree st(k+1);
      int ans = 0; 
      for (int i=sz-1; i>=0; --i)  {
        int v = nums[i];
        //cout << "v = " << v << " " << "query(0, " << dic[v]-1<< endl; 
        tmp[i] = st.query(0, dic[v]-1);
        st.update(dic[v], dic[v], 1);
      }

      return tmp; 
    }
};

int main() {
  return 0;
}
