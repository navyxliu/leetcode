#include <vector>
#include <string>
#include <unordered_map>
using namespace std; 

class WordDistance {
    unordered_map<string, int> index;
    vector<vector<int>> cache;

public:
    WordDistance(vector<string>& words) {
        int sz = words.size();
        int i = 0;
        for (auto & s : words) {
            if (index.find(s) == index.end())
                index[s] = i++;
        }
        cache = vector<vector<int>>(i, vector<int>(i, INT_MAX));
        
        for (int i=0; i<sz; ++i)
            for (int j=i+1; j<sz; ++j) {
                int a = index[words[i]];
                int b = index[words[j]];
                if (a > b) {
                    swap(a, b);
                }

        
                cache[a][b] = min(cache[a][b], (j-i));
            }
    }

    int shortest(string word1, string word2) {
        int a = index[word1];
        int b = index[word2];

        if (a > b) {
            swap(a, b);
        }

        return cache[a][b];
    }
};



// Your WordDistance object will be instantiated and called as such:
// WordDistance wordDistance(words);
// wordDistance.shortest("word1", "word2");
// wordDistance.shortest("anotherWord1", "anotherWord2");
