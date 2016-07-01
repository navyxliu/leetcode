#include <vector>
#include <math.h>
#include <algorithm>

class SegmentTree 
{
  std::vector<int> st; // The array that stores segment tree nodes
  int n_; 

  int build(int *arr, int ss, int se, int si);

  int getMid(int s, int e) {
      return s + (e - s) / 2;
  }
 int rmqImpl(int ss, int se, int qs, int qe, int si);
public:
  SegmentTree(int *arr, int n): n_(n) {
    int x = (int) (ceil(log2(n)));
 
    //Maximum size of segment tree
    int max_size = 2 * (int) pow(2.0, (float)x) - 1;
 
    st.resize(max_size);
    build(arr, 0, n-1, 0);
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
        st[si] = arr[ss];
        return arr[ss];
    }

    // If there are more than one elements, then recur for left and
    // right subtrees and store the sum of values in this node
    int mid = getMid(ss, se);
    st[si] = std::min(build(arr, ss, mid, si * 2 + 1)
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
        return INT_MAX;;

    int mid = getMid(ss, se);
    // If a part of this segment overlaps with the given range
    return std::min(rmqImpl(ss, mid, qs, qe, 2 * si + 1),
            rmqImpl(mid + 1, se, qs, qe, 2 * si + 2));
}

#include <iostream>
using namespace std;

int main()
{
  int arr[] = {1, 3, 8, 5, -1, 7, 9, 11};
  int n = sizeof(arr) / sizeof(int); 
  SegmentTree * tree = new SegmentTree(arr, n);

  // Find sum after the value is updated
  cout << "Updated sum of values in given range = "
           << tree->rmq(6, 7) << "\n";
  cout << "Updated sum of values in given range = "
           << tree->rmq(1, 6) << "\n";
  cout << "Updated sum of values in given range = "
           << tree->rmq(0, 3) << "\n";
}

