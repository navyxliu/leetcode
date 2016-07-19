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
enum {
  WHITE, GRAY, BLACK
};

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

  void dfs(int i, vector<int>& color, vector<string>& wip, vector<vector<string>>& paths, int maxdepth, int target) {
    //cout << "i = " << i << "depth " << wip.size() << "\n";
    if (i == target) {
      wip.push_back(vertices[target]->w); 
      paths.push_back(wip);
      wip.pop_back();
      return;
    } 
    else if (wip.size() >= maxdepth) return;
    else {
      color[i] = GRAY;
      Node * t = vertices[i];  
      wip.push_back(t->w);
      Edge * e = t->e;
      while (e) {
        if (color[e->target()] != GRAY)
          dfs(e->target(), color, wip, paths, maxdepth, target);  

        e = e->next;
      }
      color[i] = BLACK;
      wip.pop_back();
    }
  } 
  void allshortestPaths(int u, int v, vector<vector<string>>& paths) {
    int sz = size();
    int length = shortestPath(u, v);
    cout << "length " << length << "\n";

    vector<int> color(sz, WHITE);    
    vector<string> wip;
    dfs(u, color, wip, paths, length, v);
  }

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
 
  void addNodeToPath(const Node * node, int i, int sz, int pos, vector<vector<string>>& paths) {
    if (i >= paths.size()) paths.push_back(vector<string>(sz));
    paths[i][sz - pos - 1] = node->w;
  } 
};

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string>& wordList) {
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

      vector<vector<string>> ans;
      G.allshortestPaths(i, j, ans);
      return ans; 
    }
};


int main() {
#if 0
#if 1
  unordered_set<string> wordList = {"hot","dot","dog","lot","log"};
  string beginWord = "hit";
  string endWord = "cog";
#else
  unordered_set<string> wordList = {"ted","tex","red","tax","tad","den","rex","pee"};
  string beginWord = "red";
  string endWord = "tax";
#endif
#endif
string beginWord = "cet";
string endWord = "ism";
  unordered_set<string> wordList = {"kid","tag","pup","ail","tun","woo","erg","luz","brr","gay","sip","kay","per","val","mes","ohs","now","boa","cet","pal","bar","die","war","hay","eco","pub","lob","rue","fry","lit","rex","jan","cot","bid","ali","pay","col","gum","ger","row","won","dan","rum","fad","tut","sag","yip","sui","ark","has","zip","fez","own","ump","dis","ads","max","jaw","out","btu","ana","gap","cry","led","abe","box","ore","pig","fie","toy","fat","cal","lie","noh","sew","ono","tam","flu","mgm","ply","awe","pry","tit","tie","yet","too","tax","jim","san","pan","map","ski","ova","wed","non","wac","nut","why","bye","lye","oct","old","fin","feb","chi","sap","owl","log","tod","dot","bow","fob","for","joe","ivy","fan","age","fax","hip","jib","mel","hus","sob","ifs","tab","ara","dab","jag","jar","arm","lot","tom","sax","tex","yum","pei","wen","wry","ire","irk","far","mew","wit","doe","gas","rte","ian","pot","ask","wag","hag","amy","nag","ron","soy","gin","don","tug","fay","vic","boo","nam","ave","buy","sop","but","orb","fen","paw","his","sub","bob","yea","oft","inn","rod","yam","pew","web","hod","hun","gyp","wei","wis","rob","gad","pie","mon","dog","bib","rub","ere","dig","era","cat","fox","bee","mod","day","apr","vie","nev","jam","pam","new","aye","ani","and","ibm","yap","can","pyx","tar","kin","fog","hum","pip","cup","dye","lyx","jog","nun","par","wan","fey","bus","oak","bad","ats","set","qom","vat","eat","pus","rev","axe","ion","six","ila","lao","mom","mas","pro","few","opt","poe","art","ash","oar","cap","lop","may","shy","rid","bat","sum","rim","fee","bmw","sky","maj","hue","thy","ava","rap","den","fla","auk","cox","ibo","hey","saw","vim","sec","ltd","you","its","tat","dew","eva","tog","ram","let","see","zit","maw","nix","ate","gig","rep","owe","ind","hog","eve","sam","zoo","any","dow","cod","bed","vet","ham","sis","hex","via","fir","nod","mao","aug","mum","hoe","bah","hal","keg","hew","zed","tow","gog","ass","dem","who","bet","gos","son","ear","spy","kit","boy","due","sen","oaf","mix","hep","fur","ada","bin","nil","mia","ewe","hit","fix","sad","rib","eye","hop","haw","wax","mid","tad","ken","wad","rye","pap","bog","gut","ito","woe","our","ado","sin","mad","ray","hon","roy","dip","hen","iva","lug","asp","hui","yak","bay","poi","yep","bun","try","lad","elm","nat","wyo","gym","dug","toe","dee","wig","sly","rip","geo","cog","pas","zen","odd","nan","lay","pod","fit","hem","joy","bum","rio","yon","dec","leg","put","sue","dim","pet","yaw","nub","bit","bur","sid","sun","oil","red","doc","moe","caw","eel","dix","cub","end","gem","off","yew","hug","pop","tub","sgt","lid","pun","ton","sol","din","yup","jab","pea","bug","gag","mil","jig","hub","low","did","tin","get","gte","sox","lei","mig","fig","lon","use","ban","flo","nov","jut","bag","mir","sty","lap","two","ins","con","ant","net","tux","ode","stu","mug","cad","nap","gun","fop","tot","sow","sal","sic","ted","wot","del","imp","cob","way","ann","tan","mci","job","wet","ism","err","him","all","pad","hah","hie","aim","ike","jed","ego","mac","baa","min","com","ill","was","cab","ago","ina","big","ilk","gal","tap","duh","ola","ran","lab","top","gob","hot","ora","tia","kip","han","met","hut","she","sac","fed","goo","tee","ell","not","act","gil","rut","ala","ape","rig","cid","god","duo","lin","aid","gel","awl","lag","elf","liz","ref","aha","fib","oho","tho","her","nor","ace","adz","fun","ned","coo","win","tao","coy","van","man","pit","guy","foe","hid","mai","sup","jay","hob","mow","jot","are","pol","arc","lax","aft","alb","len","air","pug","pox","vow","got","meg","zoe","amp","ale","bud","gee","pin","dun","pat","ten","mob"};

  Solution sol;

  auto ans = sol.findLadders(beginWord, endWord, wordList);
  for (auto & v : ans) {
    for (auto &s : v) {
      cout << s << "->";
    }
    cout << "\n";
  }
}
