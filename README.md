# Data Structure
## Heap
* skyline.cpp
## Binary-Search-Tree
### Red-Black-Tree
* `template` rbtree.cpp
## Monotonic Queue
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
---
# Graph
## Disjoint Set or Union-Find Algorithm
## Dijkstra (greedy)
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
---
# String
## Trie

# Miscellaneous
## [faster IO](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull): disable the synchronization between stdio and c++ stream library; untie cin from cout.
```cpp
int speed_up = []{
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    return 0;
}();
```