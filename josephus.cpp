//many interviewers asked me to erase one element from a circular linked list. 
//I always wonder why... I found simulation of Josephus circle needs that operation.

//14.2 CLRS p.318
#include <vector>
#include <iostream>
using namespace std; 

//figure out the last survior 
//@param n: the number of people
//@param k: count k and then kill
int survior(int n, int k) {
  if (n == 1) {
    return 1; 
  }
  else {
    int ans = (survior(n-1, k) + k - 1) % n + 1;
    return ans; 
  }
}

template <class T>
class Node { //node of a cyclic list
  T val; 

  Node(T x) : val(x), next(NULL) {}
public:
  Node * next; 

  void erase() { // for a cricle, next is not null
    Node * p = this->next; 

    val = p->val; 
    next = p->next; 

    delete p; 
  }

  static Node * create(T x) {
    return new Node(x);
  }
  T value() const { return val; }
  T& value() { return val; }
};

//calculate the josephus permutation
void josephus(int n, int k, vector<int>& perm) {
  Node<int> * h = Node<int>::create(1);

  Node<int> * p = h;
  for (int i=2; i<=n; ++i) {
    p->next = Node<int>::create(i);
    p = p->next; 
  } 
  p->next = h; 
  p = h; 

  int sz = n; 

  for (int i=0; i<n; ++i) {
    int kk = (k-1) % sz + 1;  //tiny optization. in case that k is larger than sz

    for (int j=1; j<kk; ++j) {
      p = p->next;       
    }    

    perm[i] = p->value();
    p->erase();
    sz--; 
  }
}

int main(int argc, char * argv[]) {
  int n = atoi(argv[1]); int k = atoi(argv[2]); 
  cout << "n = " << n  << " k = " << k << "\n";

  vector<int> perm(n);
  cout << survior(n, k);
  cout << "\n";
   
  josephus(n, k, perm);
  cout << "["; 
  for (auto v: perm) {
    cout << v << ", ";
  }
  cout << "]\n";
}
