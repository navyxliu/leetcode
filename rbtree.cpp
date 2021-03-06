#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std; 

template<class K, class V>
struct Node {
  Node *left, * right; 
  K key; 
  V value; 
  bool color; 
  int size;

  Node(K k, V val, bool col, int sz): key(k), value(val), color(col), size(sz)
  {
    left = right = NULL; 
  }
};

template <class K, class V>
class RBTree {
  static const bool BLACK = false; 
  static const bool RED = true; 

  Node<K, V> * root; 
private: 
  bool isRed(Node<K, V> * x) const {
    if (x == NULL) return false; 
    return x->color == true; 
  }
  int size(Node<K, V> * x) const {
    return x == NULL ? 0 : x->size;
  }

  V& get(Node<K, V> * x, K key) {
    while (x != NULL) {
      if (key == x->key) return x->value;
      else if (x->key < key) {
        x = x->right;  
      }
      else
        x = x->left; 
    }

    insert(key, V());
    return get(root, key);
  }


public: 
  RBTree() : root(nullptr) {}

  V& get(K key) {
    return get(root, key);
  }
  void put(K key, V val) {
    root = insert(root, key, val);
    root->color = BLACK; 
  }

  int size() const {
    return size(root); 
  }
  K min() const {
    return min(root).key; 
  }
  
  bool contains(K key) const {
    Node<K, V> * x = root; 

    while (x != NULL) {
      if (key == x->key) break;
      else if (x->key < key) {
        x = x->right;  
      }
      else
        x = x->left; 
    }
    return x != NULL; 
  } 

  Node<K, V> * insert(K key, V val) {
    return insert(root, key, val);  
  }

  int height() const {
    if (!root) return 0;

    int h = 0;    
    dfs(root, 1, h); 
    return h; 
  }

  void erase(K key) {
    if (!contains(key)) return;
    if (!isRed(root->left) && !isRed(root->right))
      root->color = RED;
    root = erase(root, key);
    if (!isEmpty()) root->color = BLACK;
  }

  bool isEmpty() const {
    return this->root == NULL;
  }

  void deleteMin() {
    if (!isRed(root->left) && !isRed(root->right))
      root->color = RED;

    root = deleteMin(root);
    if (!isEmpty()) root->color = BLACK;
  }  

  int rank(K key) const {
      return rank(root, key);
  }

  K select(int i) {
    Node<K, V> * p = select(root, i);
    return p->value;
  }

protected: 

  Node<K, V>* select(Node<K, V>* x, int k) {
    int t = size(x->left);

    if (t > k) return select(x->left, k);
    else if (t < k) return select(x->right, k - t - 1);
    else
        return x;
  }

  int rank(Node<K, V> * x, K key) const {
      if (x == NULL) return 0;

      if (x->key == key) return size(x->left);
      else if (x->key < key) {
        return 1 + size(x->left) + rank(x->right, key);
      }
      else {//x->key > key
        return rank(x->left, key);
      }
  }

  Node<K,V>* min(Node<K,V>* x) {
    if (x->left == NULL) return x; 
    else 
      return min(x->left);
  } 
  Node<K,V>* moveRedLeft(Node<K,V>* h) {
    flipColors(h);
    if (isRed(h->right->left)) {
      h->right = rotateRight(h->right);
      h = rotateLeft(h);
      flipColors(h);
    }
    return h; 
  }
  Node<K,V>* moveRedRight(Node<K,V>* h) {
    flipColors(h);
    if (isRed(h->left->left)) {
      h = rotateRight(h);
      flipColors(h);
    }
    return h; 
  }
  Node<K,V>* deleteMin(Node<K,V>* h) {
    if (h->left == NULL) return NULL;
    if (!isRed(h->left) && !isRed(h->left->left)) 
      h = moveRedLeft(h);

    h->left = deleteMin(h->left); 
    return balance(h);
  }

  Node<K, V>* erase(Node<K,V>* h, K key) {
    if (key < h->key) {
      if (!isRed(h->left) && !isRed(h->left->left))
        h = moveRedLeft(h);
      h->left = erase(h->left, key);
    }
    else {
      if (isRed(h->left)) 
        h = rotateRight(h);
      if (key == h->key && h->right == NULL) 
        return NULL; 
      if (!isRed(h->right) && !isRed(h->right->left))
        h = moveRedRight(h);

      if (key == h->key) {
        Node<K,V>* x = min(h->right);
        h->key = x->key; 
        h->value = x->value;  
        h->right = deleteMin(h->right);
      }
      else h->right= erase(h->right, key);
    }
    return balance(h);
  }

  void dfs(Node<K, V>* t, int sofar, int& h) const {
    if (!t->left && !t->right) {
      h = max(h, sofar);
    } 

    if (t->left) {
      dfs(t->left, sofar+1, h);
    }

    if (t->right) {
      dfs(t->right, sofar+1, h);
    }
  }

  Node<K,V>* balance(Node<K,V>* h) {
    if (isRed(h->right)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left))
      h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) 
      flipColors(h);

    h->size = 1+size(h->left)+size(h->right);
    return h;
  }

  Node<K,V> * insert(Node<K, V> * h, K key, V val) {
    if (h == NULL) return new Node<K,V>(key, val, true, 1);
    
    if (key < h->key)
      h->left = insert(h->left, key, val);
    else if (key > h->key)
      h->right = insert(h->right, key, val);
    else 
      h->value = val;

    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);    
    if (isRed(h->left) && isRed(h->right)) flipColors(h);
  
    h->size = 1 + size(h->left) + size(h->right);
    return h; 
  }

  Node<K,V> * rotateLeft(Node<K, V> * h) {
    Node<K, V> * x = h->right; 
    h->right = x->left; 
    x->left = h; 
    x->color = h->color; 
    h->color = RED; 
    x->size = h->size;
    h->size = 1 + size(h->left) + size(h->right);
    return x; 
  }
  
  Node<K, V> * rotateRight(Node<K, V> * h) {
    Node<K, V> * x = h->left; 
    h->left = x->right; 
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->size = h->size;
    h->size = 1 + size(h->left) + size(h->right);
    return x; 
  } 

  void flipColors(Node<K, V>* h) {
    h->color = !h->color; 
    h->left->color = !h->left->color; 
    h->right->color = !h->right->color; 
  }
};

int main() {
  RBTree<int, int> tree; 
  tree.put(1, 100);
  cout << tree.get(1) << "\n";
  tree.put(2, 200);
  cout << "contains 0: " << boolalpha << tree.contains(0) << "\n";
  tree.put(0, 30);
  
  cout << "contains 0: " << boolalpha << tree.contains(0) << "\n";
  cout << tree.get(0) << "\n";
  cout << tree.get(2) << "\n";
  cout << tree.get(10) << "\n";
  tree.get(10) = 12;  
  cout << tree.get(10) << "\n"; 
  cout << tree.height() << "\n";  
  for (int i=0; i<=1000; ++i) {
    tree.put(i, 2*i+1);
  }
  cout << tree.height() << "\n";
  cout << tree.get(1000) << "\n";
  tree.erase(1000);
  cout << "tree contains 1000 " << tree.contains(1000) << "\n";
  tree.deleteMin();
  cout << "tree contains 0" << tree.contains(0) << "\n"; 
  while (tree.size() > 0) {
    tree.deleteMin(); 
  }
  cout << tree.size() << "after delete\n";
  for (int i=0; i<10; ++i) {
      tree.put(i, i+1);
  }
  tree.erase(4);
  tree.erase(5);
  for (int i=0; i<10; ++i) {
      if (i == 4 || i == 5) continue;
      cout << "tree i = " << i << " val = " << tree.get(i) << " rank = "  << tree.rank(i) << "\n";
  }

  for (int i=0; i<8; ++i) {
      cout << "tree select " << i << " " << tree.select(i) << "\n";
  }
}
