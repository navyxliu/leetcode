#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std; 

template <class T, class C = std::less<T> >
class Heap {
public:
    void push(T x) {
        arr.push_back(x);
        
        siftup(arr.size()-1);
    }
    
    void pop() {
        swap(arr[0], arr.back());
        arr.pop_back();
        siftdown(0);
    }
    T top() const { return arr[0]; } 
    size_t size() const { return arr.size(); }
    bool empty() const { return 0 == arr.size(); }
protected:
    void siftdown(int i)
    {
        int sz = arr.size();
        int k = i * 2 + 1;
        
        while (k < sz) {
            if (k+1 < sz && cmp(arr[k], arr[k+1]))
                k++; 
            if (!cmp(arr[i], arr[k])) break;
            swap(arr[i], arr[k]);
            
            i = k; 
            k = 2 * i + 1;
        }
    }
    
    void siftup(int i) {
        while (i > 0) {
            int p = (i-1)/2;
            
            if (!cmp(arr[p], arr[i])) break;
            swap(arr[p], arr[i]);
            i = p;
        }
    }
    
private: 
    vector<T> arr; 
    C cmp;
};

class MedianFinder {
    Heap<int> left; 
    Heap<int, greater<int> > right; 
    
public:

    // Adds a number into the data structure.
    void addNum(int num) {
        if (left.empty() || num > left.top())
            right.push(num);
        else 
            left.push(num);
        
        if (left.size() + 1 < right.size())
        {
            int t = right.top(); right.pop();
            left.push(t);
        }
        else if (right.size()+1 < left.size())
        {
            int t = left.top(); left.pop();
            right.push(t);
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if (left.size() == right.size())
        {
            double m = left.top();
            m += right.top();
            return m/2; 
        }    
        else if (left.size() > right.size()) {
            return (double)left.top();
        }
        else {
            return (double)right.top();
        }
    }
};

int main() {
#if 0
  Heap<int, std::greater<int> > mh;
  mh.push(1);
  mh.push(4);
  mh.push(2);
  mh.push(-1);
  mh.push(12); 
  while (mh.size() > 2) cout << mh.pop() << " ";
  cout << "\n";
  mh.push(1);
  mh.push(8);
  while (mh.size() > 0) cout << mh.pop() << " ";
  cout << "\n";
#endif
  MedianFinder finder;
  finder.addNum(2);
  cout << finder.findMedian() << " "; 
  finder.addNum(3);
  cout << finder.findMedian() << " ";
  finder.addNum(4);
  cout << finder.findMedian() << " ";  
  finder.addNum(1);
  cout << finder.findMedian() << " ";  
  finder.addNum(8);
  cout << finder.findMedian() << " ";  
  cout << "\n";
}
