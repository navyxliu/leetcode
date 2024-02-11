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