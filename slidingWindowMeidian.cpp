/**
 * A max/min heap that supports erase by value
 */
#ifndef _HASHHEAP_H_
#define _HASHHEAP_H_

#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std; 

enum class HeapType {
  minheap,
  maxheap
};

template<typename T>
class HashHeap {
  struct Node {
    int id;
    int count;
    Node(int i, int c) : id(i), count(c) {}
    Node() {}
  };

  int count;
  HeapType type;
  std::vector<T> heap;
  std::unordered_map<T, Node> hash;

  int parent(int i) {return (i-1) / 2;}
  int lson(int i) {return 2*i+1;}
  int rson(int i) {return 2*i+2;}

  bool comp_less(const T &lhs, const T &rhs) {
    if (type == HeapType::maxheap) {
      return lhs < rhs;
    } else {
      return rhs < lhs;
    }
  }

  void _swap(int i, int j) {
    std::swap(hash[heap[i]].id, hash[heap[j]].id);
    std::swap(heap[i], heap[j]);
  }

  void siftUp(int i) {
    while (parent(i) >= 0 && comp_less(heap[parent(i)], heap[i])) {
      _swap(i, parent(i));
      i = parent(i);
    }
  }

  void siftDown(int i) {
    int j = lson(i);
    while (j < heap.size()) {
      if (rson(i) < heap.size() && comp_less(heap[j], heap[rson(i)])) {
        j = rson(i);
      }
      if (comp_less(heap[j], heap[i])) {
        break;
      } else {
        _swap(i, j);
        i = j;
        j = lson(i);
      }
    }
  }

public:
  HashHeap(HeapType t) : type(t), count(0) {}

  int size() {return count;}
  bool empty() {return size() == 0;}

  void push(T x) {
    if (hash.find(x) != hash.end()) {
      ++hash[x].count;
    } else {
      heap.push_back(x);
      hash[x] = Node(heap.size() - 1, 1);
      siftUp(heap.size() - 1);
    }
    ++count;
  }

  void pop() {
    erase(top());
  }

  T top() {return heap[0];}

  bool erase(T x) {
    if (hash.find(x) == hash.end()) 
      return false; 

    if (--hash[x].count == 0) {
      int i = hash[x].id;
      _swap(i, heap.size() - 1);

      heap.pop_back();
      hash.erase(x);

      if (parent(i) >= 0 && comp_less(heap[parent(i)], heap[i])) {
        siftUp(i);
      } else {
        siftDown(i);
      }
    }

    --count;
    return true; 
  }

  size_t size() const { return count; }
  void clear() {
    heap.clear();
    hash.clear(); 
    count = 0; 
  }
};

#endif
class Solution {
    HashHeap<int> left;
    HashHeap<int> right;
 
public:
    Solution() : left(HeapType::maxheap), right(HeapType::minheap) {}
    /**
     * @param nums: A list of integers.
     * @return: The median of the element inside the window at each moving
     */
    vector<int> medianSlidingWindow(vector<int> &nums, int k) {
        // write your code here
        left.clear();
        right.clear();         
        vector<int> ans; 
        int sz = nums.size();

        for (int i=0; i<k; ++i) {
          add(nums[i]);
        }
        for (int i=k; i<sz; ++i) {
          ans.push_back(median());

          remove(nums[i-k]); 
          add(nums[i]);
        }        
        if (left.size() + right.size() >= k) 
          ans.push_back(median());
        return ans; 
    }

    void remove(int i) {
      if (!left.erase(i)) 
        right.erase(i);  

      rebalance();
    }

    void add(int i) {
      if (left.empty() || i > left.top()) right.push(i);
      else left.push(i);
      rebalance();
    }

    void rebalance() {
      if (left.size() > right.size()+1) {
        int t = left.top(); left.pop();
        right.push(t);
      }
      else if (left.size() + 1 < right.size()) {
        int t = right.top(); right.pop();
        left.push(t);
      }
    }

    int median() {
      if (left.size() >= right.size()) {
        return left.top();
      }
      else
        return right.top();
    }
};
#include <iostream>
int main() {
  vector<int> vec = {1,2,7}; // {1,2,3,4,1,0,2};
  Solution sol; 
  auto ans = sol.medianSlidingWindow(vec, 2); 
  for (auto & i : ans) {
    cout << i << " "; 
  }
  cout << "\n";
}
