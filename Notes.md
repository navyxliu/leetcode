# Data Structure
## Priority Queue
* skyline.cpp
### variants
Index priority queue, or IndexPQ adds another level of indirection.
It provides a heapified vector. It allows to adjust items which have already been in the priority queue. One example is [indexedMinPQ](https://algs4.cs.princeton.edu/24pq/IndexMinPQ.java.html)

Modifier:
```cpp
insert(int idx, Item item)->void
change(int idx, Item item)->void
```
Accessors:
```cpp
top()->idx
operator[](int k)->Item
```
## Tree
### BFS
[2 passes of BFS can determine the diameter of a tree](https://leetcode.com/problems/tree-diameter/editorial/#approach-1-farthest-nodes-via-bfs).
### DFS
### Morris preorder traversal
Morris is a variant of DFS. Conventional DFS is O(N) space complexity because of stack. Morris exploits the right-most TreeNode's right pointer, which is supposed to be null anyway.
The rightmost node is refered to as 'predecessor'. prodecessor.light roles as a signal light.
1) for the 1st time we encounter it, set it to the successor, turn left.
2) for the 1nd time we encounter it, recover it back to null and turn right.
It's noteworthy this isn't free. Morris's has to identify 'predecessor' at most twice. The total time complexity is still O(N) though.
* sum_root_to_leaf_sum.cpp
### Binary Search Tree
#### Red-Black-Tree
* `template` rbtree.cpp
## Qsort/Qselect
## Monotonic Queue/Stack
The key is to maintain monotone for one property of the elements in the container. We could use it as a queue or stack.
it is particularly handy when we implement some linear algorithms such as sliding window.
* `template` mqueue.cpp
* prob239.cpp
## Range/Interval
### [Segment Tree](https://cp-algorithms.com/data_structures/segment_tree.html): divide & conquer algorithm.
* `template` array-based fixed range-sum: segtree.cpp
* `template` fixed RMQ: rmq.cpp
* dynamic range-query: range-module.cpp
### Interval tree
* `template` interval_tree.cpp
### Binary Indexed Tree(BIT)
* `template`: bit.cpp
* prob307-2.cpp, prob-308-bit.cpp
## Disjoint Set or Union-Find Algorithm
* islands2.cpp
---
# Graph
## Single-Point-Shortest-Path
### Dijkstra
In the nutshell, Dijkstra is same as Prim's. Prim's is greedy with the spanning tree. Dijkstra's generates SPT(Single-Point-Tree) with relaxing operation.
* prob1514-dijkstra.cpp
### Bellman-Ford
## DAG algorithm
By definition, DAG doesn't contain any cycle. The algorithm just relax vertices in topological order.
This approach is straight-forward and can solve both the shortest path and the longest path.
To discover the longest path, we just negate all weights of edges.

### Summary
| Contain negative weight | Acyclic | Algorithm            | Time-complexity |   |
|-----------------|---------|----------------------|-----------------|---|
|                 |         | Bellman-Ford         | EV              |   |
| no              |         | Dijkstra             | ElogV (binary heap)      |   |
|                 | yes     | DAG | EV           |   |
## LCA on tree
### Recursive solution
* prob236-lca.cpp
### Euler tour + RMQ
### Binary lifting
### Two pointers
Each node requires to contain its parent pointer. Comparing to hashtable solution, this trick has O(1) space complexity.
* prob1650-lca.cpp
## Topological order
* DFS
* in-degree
## Cycle Detection
Floyd's Tortoise and Hare Algorithm

# Binary Search
Binary search is an algorithm. The basic idea is that we half the search space in each trial.
We must forget about a general template to solve all problems. It doesn't exist like other algorithms.

The trick is we need to tell whether we inspect its neighbors during binary searching.
If we don't have any interaction with its neighters, we could use Template-I:
```cpp
int binarySearch(vector<int>& nums, int target){
  int left = 0, right = nums.size() - 1;
  while(left <= right){
    // Prevent (left + right) overflow
    int mid = left + (right - left) / 2;
    if(nums[mid] == target){ return mid; }
    else if(nums[mid] < target) { left = mid + 1; }
    else { right = mid - 1; }
  }

  // End Condition: left > right
  return -1;
}
```
Sometimes, we do need to include the midpoint in a search sub-space. eg. we want to search the 1st element that is greater or equal(>=) to the target in an integer arry. We should go with Template-II. A mistep of template-I is that we end up with an inifinite loop for some data.

```cpp
if (nums.size() == 0) {
    return -1;
}

int lo = 0;
int hi = nums.size()-1;
while (lo < hi) {  // we must use < here. It ensures that there're at least 2 elements in the search space.
                   // we we use <= here, then there's only one element in the last search space.
                   // If controlflow takes hi = mid, it will not shrink the search space!
                   // try nums[1, 2] and target == 1
    int mid  = lo + (hi-lo)/2;
    if (nums[mid] < target) { // we are looking >= target, we can ditch the entire left space.
        lo = mid+1;
    } else {                  // now nums[mid] >= target, we have to retain 'mid' here.
        hi = mid;
    }
}
// post-process num[lo]. this handles the only corner case: only 1 element left.
return lo;
```

Last, it's possible that both left and right sub-spaces include the midpoint. if so, we use template-III.
```cpp
int binarySearch(vector<int>& nums, int target){
    if (nums.size() == 0)
        return -1;

    int left = 0, right = nums.size() - 1;
    while (left + 1 < right){           // by writing this, it guarantes that there are at least 3 elements in the search space.
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {// ditch [mid+1, high]
            left = mid;
        } else {                        // ditch [lo, mid-1]
            right = mid;
        }
    }

    // Post-processing: we have to handle two corner cases: 1 element or 2 elements.
    // End Condition: left + 1 == right
    if(nums[left] == target) return left;
    if(nums[right] == target) return right;
    return -1;
}
```
The easiest way of using binary search is to invoke the procedures defined in <algorithm>. It has a constraint: they only work with a concret sorted range. We can't perform binary search on a virtual space. If we want to use custom comparator such as greater, we need to ensure that range [Begin, End) is ordered according to the comparator.
* lower_bound: return the 1st element that is >= __value
* upper_bound: return the 1st element that is > __value

# Dynamic programming
* LCS: longest_common_subsequence.cpp
* partition_equal_subset_sum: using std::optional as memoization
---
# String
## Trie

# Random Alglrithm
## Reservoir sampling
* sampling.cpp

# Compiler
* Linear Scan Register Allocation: meetingRoom2.cpp
