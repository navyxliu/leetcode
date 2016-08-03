#include <vector> 
#include <string>
#include <iostream>
using namespace std; 

class Comparator2 {
    public:
     int cmp(string a, string b) {
       if (a == b) return 0; 
       else if (a < b) return -1; 
       return 1; 
     }
};

class Comparator {
    string tolower(const string& s) {
      string res = s;

      for (int i=0,len=s.size(); i<len; ++i) {
        if (s[i] >='A' && s[i] <='Z') res[i] = 'a' + (s[i] - 'A');
      }
      return res; 
    }

public:
    int cmp(string a, string b) {
       a = tolower(a);
       b = tolower(b);

       if (a == b) return 0; 
       else if (a < b) return -1; 
       return 1; 
    }
};

class Solution {
public:
    /**
     * @param nuts: a vector of integers
     * @param bolts: a vector of integers
     * @param compare: a instance of Comparator
     * @return: nothing
     */
    void sortNutsAndBolts(vector<string> &nuts, vector<string> &bolts, Comparator compare) {
        // write your code here
        int n = nuts.size();

        mysort(nuts, bolts, 0, n-1, compare);
    }
    
    void mysort(vector<string>& nuts, vector<string>& bolts, int lo, int hi, Comparator compare) {
        if (hi - lo + 1 < 2) return ; 

        cout << "before partition\n";
        cout << "nuts: [";
        for (auto & n: nuts) cout << n << ",";
        cout << "]\n";
        
        cout << "bolts: [";
        for (auto & b: bolts) cout << b << ",";
        cout << "]\n";
       
        int pivot = partition2(nuts, lo, hi, bolts[hi], compare);
        cout << "pivot where" << pivot << "\n";

        partition2(bolts, lo, hi, nuts[pivot], compare);

        cout << "after partition\n";
        cout << "nuts: [";
        for (auto & n: nuts) cout << n << ",";
        cout << "]\n";
        
        cout << "bolts: [";
        for (auto & b: bolts) cout << b << ",";
        cout << "]\n";
       
        mysort(nuts, bolts, lo, pivot-1, compare);
        mysort(nuts, bolts, pivot+1, hi, compare);
    }
    
    int partition(vector<string>& arr, int lo, int hi, const string& pivot, Comparator compare) {
        while (lo<hi) {
            while (lo<hi && compare.cmp(arr[lo], pivot) == -1)
                lo++; 
            while (lo<hi && compare.cmp(pivot, arr[hi]) == -1)
                hi--; 
            
            if (lo == hi) break; 
            
            swap(arr[lo], arr[hi]);
            lo++; 
            hi--; 
        }
        
        return lo; 
    }

    int partition2(vector<string>& arr, int lo, int hi, const string& pivot, Comparator compare) {
        int i = lo; 
        for (int j=lo; j<hi; ++j) {
            int res = compare.cmp(arr[j], pivot); 
            if (res == 0) {
                swap(arr[j], arr[hi]);
                j--; 
            }
            else if (res == -1) {
                swap(arr[i], arr[j]);
                i++; 
            }
        }
        swap(arr[i], arr[hi]);
        return i; 
    }
};

int main() {
  //vector<string> nuts = {"1", "2", "3", "4", "5", "6"};
  //vector<string> bolts = {"3", "4", "6", "5", "1", "2"};    
  //vector<string> nuts = {"@", "#", "$", "%", "^", "&"};
  //vector<string> bolts = {"$", "%", "&", "^", "@", "#"};
  //Comparator cmp;
  vector<string> nuts = {"ab","bc","dd","gg"}; 
  vector<string> bolts = {"AB","GG","DD","BC"};
  Comparator cmp; 

  Solution sol; 
  sol.sortNutsAndBolts(nuts, bolts, cmp);

  cout << "nuts:  ";
  for (auto& s: nuts) cout << s << " ";
  cout << "\n";

  cout << "bolts: ";
  for (auto& s: bolts) cout << s << " ";
  cout << "\n";
}
