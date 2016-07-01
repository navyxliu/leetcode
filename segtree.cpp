#include <vector>
#include <math.h>

class SegmentTree 
{
  std::vector<int> st; // The array that stores segment tree nodes
  int n_; 

  int build(int *arr, int ss, int se, int si);

  int getMid(int s, int e) {
      return s + (e - s) / 2;
  }
  int getSumImpl(int ss, int se, int qs, int qe, int si);
  void updateValueImpl(int ss, int se, int i, int diff, int si)
    {
        // Base Case: If the input index lies outside the range of 
        // this segment
        if (i < ss || i > se)
            return;
 
        // If the input index is in range of this node, then update the
        // value of the node and its children
        st[si] = st[si] + diff;
        if (se != ss) {
            int mid = getMid(ss, se);
            updateValueImpl(ss, mid, i, diff, 2 * si + 1);
            updateValueImpl(mid + 1, se, i, diff, 2 * si + 2);
        }
    }
 
public:
  SegmentTree(int *arr, int n): n_(n) {
    int x = (int) (ceil(log2(n)));
 
    //Maximum size of segment tree
    int max_size = 2 * (int) pow(2.0, (float)x) - 1;
 
    st.resize(max_size);
    build(arr, 0, n-1, 0);
  }
  int getSum(int qs, int qe) {
    return getSumImpl(0, n_-1, qs, qe, 0);
  }
  void updateValue(int idx, int diff) {
     updateValueImpl(0, n_ - 1, idx, diff, 0);
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
    st[si] = build(arr, ss, mid, si * 2 + 1) +
             build(arr, mid + 1, se, si * 2 + 2);
    return st[si];
}

int SegmentTree::getSumImpl(int ss, int se, int qs, int qe, int si)
{
    // If segment of this node is a part of given range, then return
    // the sum of the segment
    if (qs <= ss && qe >= se)
        return st[si];

    // If segment of this node is outside the given range
    if (se < qs || ss > qe)
        return 0;

    // If a part of this segment overlaps with the given range
    int mid = getMid(ss, se);
    return getSumImpl(ss, mid, qs, qe, 2 * si + 1) +
            getSumImpl(mid + 1, se, qs, qe, 2 * si + 2);
}

#include <iostream>
using namespace std;

int main()
{
  int arr[] = {1, 3, 5, 7, 9, 11};
  int n = sizeof(arr) / sizeof(int); 
  SegmentTree * tree = new SegmentTree(arr, n);

  // Build segment tree from given array

  // Print sum of values in array from index 1 to 3
  cout << "Sum of values in given range = "
         << tree->getSum(1, 3) << "\n";

  // Update: set arr[1] = 10 and update corresponding segment
  // tree nodes
  tree->updateValue(1, 7);

  // Find sum after the value is updated
  cout << "Updated sum of values in given range = "
           << tree->getSum(1, 3) << "\n";
}

