#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <math.h>
using namespace std; 
class WordDistance {
    unordered_map<string, vector<int>> index;

public:
    WordDistance(vector<string>& words) {
        int sz = words.size();

        for (int i=0; i<sz; ++i) {
            index[words[i]].push_back(i);
        }
    }
    int abs(int a) { return a < 0 ? -a : a; }
    int shortest(string word1, string word2) {
        vector<int>& list1 = index[word1];
        vector<int>& list2 = index[word2];
        int i = 0; int sz1 = list1.size(); 
        int j = 0; int sz2 = list2.size();
        int d = INT_MAX;
        
        while (i<sz1 && j<sz2) {
            d = min(d, abs(list1[i++] - list2[j++]));
        }
        while (i< sz1 && sz2 > 0) {
            d = min(d, abs(list1[i++] - list2[sz2-1]));
        }
        while (j < sz2 && sz1 > 0) {
            d = min(d, abs(list1[sz1-1] - list2[j++]));
        } 
        return d; 
    }
};
#include <iostream>

int main() 
{
  vector<string> v = {"a", "c", "b", "a"};
  WordDistance wd(v);
  cout << wd.shortest("b", "a");
  cout << wd.shortest("a", "b");
}
