#define CHAR_TO_INDEX(ch) (int)(ch - 'a')
#include <string>
#include <iostream>
using namespace std;
class TrieNode {
     TrieNode * kids[26];
    bool isLeaf;
   
public:
    // Initialize your data structure here.
    TrieNode() : isLeaf(false) {
        for (int i=0; i<26; ++i)
            kids[i] = nullptr;
    }

  friend class Trie;    
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode * p = root;
        
        for (int i=0, sz=word.size(); i<sz; ++i) {
            int idx = CHAR_TO_INDEX(word[i]);
            
            if (!p->kids[idx]) {
                p->kids[idx] = new TrieNode();    
            }
            p = p->kids[idx];
        }
        
        p->isLeaf = true; 
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * p = root;
        
        for (int i=0, sz=word.size(); i<sz; ++i) {
            int idx = CHAR_TO_INDEX(word[i]);
            if (!p->kids[idx]) return false;
        
            p = p->kids[idx];
        }
        
        return p->isLeaf; 
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode * p = root;
        
        for (int i=0, sz=prefix.size(); i<sz; ++i) {
            int idx = CHAR_TO_INDEX(prefix[i]);
            if (!p->kids[idx]) return false;
        
            p = p->kids[idx];
        }
        
        return true;     
    }

private:
    TrieNode* root;
};
int main() {
  Trie trie;
  trie.insert("somestring");
  cout << trie.search("key") << "\n";
  cout << trie.search("somes") << "\n";
  cout << trie.startsWith("somes") << "\n";
  trie.insert("somes");
  trie.insert("somegoogle");
  cout << trie.search("somes") << "\n";

}
