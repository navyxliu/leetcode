#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <climits>
using namespace std;
class SegmentTree 
{
  std::vector<int> st; // The array that stores segment tree nodes
  std::vector<int> arr;
  int n_;
  int build(int *arr, int ss, int se, int si);

  int getMid(int s, int e) {
      return s + (e - s) / 2;
  }

  int minVal(int i, int j)
  {
      if (i == -1) return j;
      if (j == -1) return i;
      return (arr[i] < arr[j])? i : j;
  }

  int rmqImpl(int ss, int se, int qs, int qe, int si);
public:
  SegmentTree(vector<int>& v): n_(v.size()), arr(v){

    int x = (int) (ceil(log2(n_)));
 
    //Maximum size of segment tree
    int max_size = 2 * (int) pow(2.0, (float)x) - 1;
 
    st.resize(max_size);
    build(&v[0], 0, n_-1, 0);

  }

  int rmq(int qs, int qe) {
    return rmqImpl(0, n_-1, qs, qe, 0);
  }
};

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
int SegmentTree::build(int *arr, int ss, int se, int si)
{
    // If there is one element in array, store it in current node of
    // segment tree and return
    if (ss == se) {
        return st[si] = ss; 
    }

    // If there are more than one elements, then recur for left and
    // right subtrees and store the sum of values in this node
    int mid = getMid(ss, se);
    st[si] = minVal(build(arr, ss, mid, si * 2 + 1)
             ,build(arr, mid + 1, se, si * 2 + 2));

    return st[si];
}

int SegmentTree::rmqImpl(int ss, int se, int qs, int qe, int si)
{
    // If segment of this node is a part of given range, then return
    // the sum of the segment
    if (qs <= ss && qe >= se)
        return st[si];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return -1;

    int mid = getMid(ss, se);
    // If a part of this segment overlaps with the given range
    int p1 = rmqImpl(ss, mid, qs, qe, 2 * si + 1);
    int p2 = rmqImpl(mid + 1, se, qs, qe, 2 * si + 2);
    return minVal(p1, p2);
}


class Solution {
    typedef pair<int, int> rtype;
    typedef vector<int>::iterator it;
    SegmentTree *tree; 

    int solveIt(vector<int>& hist, int l, int r){
    // Base cases
    if (l > r)  return INT_MIN;
    if (l == r)  return hist[l];
 
    // Find index of the minimum value in given range
    // This takes O(Logn)time
    int m = tree->rmq(l, r);
 
    /* Return maximum of following three possible cases
       a) Maximum area in Left of min value (not including the min)
       a) Maximum area in right of min value (not including the min)
       c) Maximum area including min */
    return max(solveIt(hist, l, m-1),
               max(solveIt(hist, m+1, r),
               (r-l+1)*(hist[m])));
    }
    
public:
    int largestRectangleArea(vector<int>& heights) {
        tree = new SegmentTree(heights);
        int ans = solveIt(heights, 0, heights.size()-1);
        //delete tree;  
        return ans;
    }
};

int main()
{
  Solution sol; 
  //vector<int> v = {2,1,5,6,2,3};
  //vector<int> v=  {6, 1, 5, 4, 5, 2, 6};
  vector<int> v(20000);
  for (int i=0; i<20000; ++i) v[i] = i;
  cout << sol.largestRectangleArea(v) << "\n";
}
