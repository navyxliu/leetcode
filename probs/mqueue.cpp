#include <vector>
#include <deque>
#include <iostream>
using namespace std; 

struct Node {
  int idx; 
  int w;
  Node(int index, int weight) : idx(index), w(weight) {}
};

class MQueue {
  deque<Node> arr; 

public: 
  void push(Node e) {
    while (!arr.empty() && arr.back().w > e.w) {
      arr.pop_back();
    }
    arr.push_back(e);
  }  

  Node top() {
    return arr.front();
  }

  void pop() {
    arr.pop_front();
  }

  int size() const {
    return arr.size();
  }
  friend class MQIterator; 
};

class MQIterator {
  MQueue * q;
  int idx; 
  
public:
  MQIterator(MQueue & mq) : q(&mq), idx(0) {}
  bool hasNext() {
    return idx < q->size();
  }

  Node& iter() {
    return q->arr[idx++];
  } 
};

int main() {
  MQueue mq; 
  mq.push(Node(1, -1));
  mq.push(Node(2, 2));
  mq.push(Node(3, 3));
  mq.push(Node(4, 1));
  cout << mq.size() << "\n";
  mq.push(Node(5, 5));

  MQIterator it(mq);
  while (it.hasNext()) {
    Node & t = it.iter();
    cout << "(" << t.idx << ", " << t.w << ") ";
  }
}
