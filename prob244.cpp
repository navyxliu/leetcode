#include <vector>
#include <string>
#include <unordered_map>
using namespace std; 
#if 0
class WordDistance {
    unordered_map<string, int> cache; 
    
public:
    WordDistance(vector<string>& words) {
        int sz = words.size();
        
        for (int i=0; i<sz; ++i) 
            for (int j=i+1; j<sz; ++j) {
                string q = words[i] + "#" + words[j];
                if (words[i] > words[j]) q = words[j]+"#"+words[i];
                if (cache.find(q) != cache.end())                
                    cache[q] = min(cache[q], (j-i));
                else 
                    cache[q] = j - i; 
            }
    }

    int shortest(string word1, string word2) {
        string q;
        if (word1 <= word2) {
            q = word1 + "#" + word2; 
        }
        else 
            q = word2 + "#" + word1;
        
        return cache[q];
    }
};
#endif
class WordDistance {
    unordered_map<string, int> index;
    unordered_map<unsigned, int> cache; 
    
public:
    WordDistance(vector<string>& words) {
        int sz = words.size();
        int i = 1; 
        for (auto & s : words) {
            if (index.find(s) == index.end())
                index[s] = i++;
        }
        
        for (int i=0; i<sz; ++i) 
            for (int j=i+1; j<sz; ++j) {
                int a = index[words[i]];
                int b = index[words[j]];
                if (a > b) {
                    swap(a, b);
                }
                
                unsigned int idx = (a<<16)|b; 
                
                if (cache.find(idx) != cache.end())                
                    cache[idx] = min(cache[idx], (j-i));
                else 
                    cache[idx] = j - i; 
            }
    }

    int shortest(string word1, string word2) {
        int a = index[word1];
        int b = index[word2];
                
        if (a > b) {
            swap(a, b);
        }
        unsigned int idx = (a<<16)|b; 
                
        return cache[idx];
    }
};


// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
