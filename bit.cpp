// C++ code to demonstrate operations of Binary Index Tree
#include <iostream>
using namespace std;
 
/*            n  --> No. of elements present in input array.   
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1]  --> Input array for whic prefix sum is evaluated. */
 
// Returns sum of arr[0..index]. This function assumes
// that the array is preprocessed and partial sums of
// array elements are stored in BITree[].
int getSum(int BITree[], int index)
{
    int sum = 0; // Iniialize result
 
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;
 
    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        // Add current element of BITree to sum
        sum += BITree[index];
 
        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return sum;
}

// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return 
// some of them (we do not know which one)

// bitMask - initialy, it is the greatest bit of MaxVal
// bitMask store interval which should be searched
int findBIT(int tree[], int bitMask, int MaxVal, int cumFre){
    int idx = 1; // this var is result of function
    
    while ((bitMask != 0) && (idx < MaxVal)){ // nobody likes overflow :)
        int tIdx = idx + bitMask; // we make midpoint of interval
        if (cumFre == tree[tIdx]) // if it is equal, we just return idx
            return tIdx;
        else if (cumFre > tree[tIdx]){ 
                // if tree frequency "can fit" into cumFre,
                // then include it
            idx = tIdx; // update index 
            cumFre -= tree[tIdx]; // set frequency for next loop 
        }
        bitMask >>= 1; // half current interval
    }
    if (cumFre != 0) // maybe given cumulative frequency doesn't exist
        return -1;
    else
        return idx;
} 
// Updates a node in Binary Index Tree (BITree) at given index
// in BITree.  The given value 'val' is added to BITree[i] and 
// all of its ancestors in tree.
void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;
 
    // Traverse all ancestors and add 'val'
    while (index <= n)
    {
       // Add 'val' to current node of BI Tree
       BITree[index] += val;
 
       // Update index to that of parent in update View
       index += index & (-index);
    }
}
int readSingleBIT(int BITree[], int idx) {
  idx = idx+1;
  int sum = BITree[idx]; 
  if (idx > 1){ // special case
    int z = idx - (idx & -idx); // make z first
    idx--; // idx is no important any more, so instead y, you can use idx
    while (idx != z){ // at some iteration idx (y) will become z
        sum -= BITree[idx]; 
        // substruct tree frequency which is between y and "the same path"
        idx -= (idx & -idx);
    }
  }
  return sum;
}
#if 0
int find(int BITree[], int n, int val) {

} 
#endif
// Constructs and returns a Binary Indexed Tree for given
// array of size n.
int *constructBITree(int arr[], int n)
{
    // Create and initialize BITree[] as 0
    int *BITree = new int[n+1];
    for (int i=1; i<=n; i++)
        BITree[i] = 0;
 
    // Store the actual values in BITree[] using update()
    for (int i=0; i<n; i++)
        updateBIT(BITree, n, i, arr[i]);
 
    // Uncomment below lines to see contents of BITree[]
    //for (int i=1; i<=n; i++)
    //      cout << BITree[i] << " ";
 
    return BITree;
}
 
 
// Driver program to test above functions
int main()
{
    int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(freq)/sizeof(freq[0]);
    int *BITree = constructBITree(freq, n);
    cout << "Sum of elements in arr[0..5] is "
         << getSum(BITree, 5);
 
    // Let use test the update operation
    freq[3] += 6;
    updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[]
 
    cout << "\nSum of elements in arr[0..5] after update is "
         << getSum(BITree, 5) << "\n";

    for (int i=0; i<n; ++i) {
      cout << readSingleBIT(BITree, i) << " ";
    } 
    cout << "\n";
    return 0;
}
