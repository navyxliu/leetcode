//word ladder
#include <queue>
#include <vector>
#include <string>
#include <unordered_set>
#include <iostream>
using namespace std;

struct Edge; 

struct Node {
  Edge * e; 
  string w;
  int idx; 
  Node(const string& s, int tgt) : w(s), idx(tgt), e(nullptr) {
  }

  void addEdge(Node * n); 

  ~Node(); 
};

struct Edge {
  Edge * next;
  Node * node;
  Edge(Node * n): node(n), next(nullptr){}

  int target() {
    if (!node) return -1;
    return node->idx; 
  }
};

int compareWords(const string& s1, const string& s2) {
  int sz = s1.size();
  int diff = 0;

  for (int i=0; i<sz; ++i) {
    if (s1[i] != s2[i]) diff++;
    if (diff > 1) break;
  }

  return diff; 
}

void Node::addEdge(Node * n){
    Edge * new_edge = new Edge(n);

    new_edge->next = e;
    this->e = new_edge; 
}

Node::~Node() {
    while (this->e) {
      Edge * n = this->e; 
      e = e->next; 
      delete n;
    }
}

struct Graph {
  vector<Node* > vertices;

  int addNode(const string& word) {
    Node * n = new Node(word, size());

    for (auto v: vertices) {
      if (compareWords(word, v->w) == 1) {
        n->addEdge(v);
        v->addEdge(n); 
      }
    }

    vertices.push_back(n);
    return n->idx;
  }

  ~Graph() {
    for (auto v: vertices) {
      delete v;   
    }    

    vertices.clear();
  } 

  int size() {
    return vertices.size();
  }
  
  int index(const string& w) {
    for (int i=0, sz=size(); i<sz; ++i) {
      if (vertices[i]->w == w) return i;
    }

    return -1;
  }

  //special case for dijkstra's algorithm
  int shortestPath(int u, int v) {
    int sz = size();
    vector<int> d(sz, INT_MAX);
    vector<bool> color(sz, false);
    queue<Node *> Q;

    Q.push(vertices[u]);
    d[u] = 0;
    
    while (!Q.empty()) {
      Node * t = Q.front();
      Q.pop();
      color[t->idx] = true;

      Edge * e = t->e;
      while (e) {
        int i = e->target();
        d[i] = min(d[t->idx] + 1, d[i]);

        if (!color[i]) //not visited
            Q.push(vertices[i]);

        e = e->next;
      }
    } 

    return d[v];
  } 
  
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& wordList) {
      if (beginWord == endWord) return 2;

      Graph G;
      for (auto w: wordList) {
        G.addNode(w);
      }

      int ignore = 0;

      int i = G.index(beginWord);
      if (i == -1) {
        i = G.addNode(beginWord);
        ignore++; 
      }
      int j = G.index(endWord);
      if (j == -1)  {
        j = G.addNode(endWord);
        ignore++;
      }  

      int dist = G.shortestPath(i, j);
      if (dist == INT_MAX) return 0;
      return dist+1;
    }
};


int main() {
  unordered_set<string> wordList = {"hot","dot","dog","lot","log"};
  string beginWord = "hot"; //"hit";
  string endWord = "hot"; //"cog";
  
  Solution sol;

  cout << sol.ladderLength(beginWord, endWord, wordList) << "\n";
}
