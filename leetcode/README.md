# What is C++ missing for leetcoder?
* range lacks python-like enumerate() https://github.com/Reedbeta/nrr_enumerate
* generic memoization https://github.com/jimporter/memo?tab=readme-ov-file
* pair/tuple doesn't support std::hash https://www.linkedin.com/pulse/generic-tuple-hashing-modern-c-alex-dathskovsky/

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