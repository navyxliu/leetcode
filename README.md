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

### Summary
| Contain negative weight | Acyclic | Algorithm            | Time-complexity |   |
|-----------------|---------|----------------------|-----------------|---|
|                 |         | Bellman-Ford         | EV              |   |
| no              |         | Dijkstra             | ElogV (binary heap)      |   |
|                 | yes     | relax in topological order | E + V           |   |
## LCA on tree
* Recursive solution
* Euler tour + RMQ
* Binary lifting
## Topological order
* DFS
* in-degree 
---
# Dynamic programming
* LCS: longest_common_subsequence.cpp
* partition_equal_subset_sum: using std::optional as memoization
---
# String
## Trie

# Compiler
* Linear Scan Register Allocation: meetingRoom2.cpp

# Miscellaneous
## [faster IO](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull): disable the synchronization between stdio and c++ stream library; untie cin from cout.
```cpp
int speed_up = []{
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    return 0;
}();
```
## Skip leetcode harness
I encoutnered another hackery in [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/). Someone just hijacks `stdout` and parses out inputs by themselves. This can reduce execution time to 0ms from about 90ms.

```cpp
int init = [] {
	cin.tie(nullptr)->sync_with_stdio(false);
    freopen("user.out", "w", stdout);

    for (string s; getline(cin, s);) {
        int solution = 0, minPrice = INT_MAX;
        for (int _i = 1, _n = s.length(); _i < _n; ++_i) {
            // parse out input, for instance [7,1,5,3,6,4]
            int price = s[_i++] & 15;
            while ((s[_i] & 15) < 10) price = price * 10 + (s[_i++] & 15);
            // real computation moved from Solution::maxProfit.
            minPrice = min(minPrice, price);
            solution = max(solution, price - minPrice);
        }
        cout << solution << '\n';
    }
    return 0;
}();

class Solution {
public:
    int maxProfit(vector<int>& arr) {
        return 0;
    }
};
```