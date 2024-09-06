#include <unordered_map>
using namespace std; 

class TwoSum {
    unordered_map<int, int> ht; 
public:
    
    // Add the number to an internal data structure.
  void add(int number) {
     ht[number]++;    
  }

    // Find if there exists any pair of numbers which sum is equal to the value.
  bool find(int value) {
      for (auto & p : ht) {
          int v = p.first; 
          int t = value - v;
          
          if (v == t && p.second >= 2)
              return true; 
          else if (v != t && ht.count(t)>0) {
              return true;
          }
      }
      
      return false; 
  }
};
