#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std; 

class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        stringstream ss;
        
        for (auto & s: strs) {
            int len = s.size();
            ss << "#" << len << "#";
            ss << s; 
        }
        return ss.str();
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> ans;
        int sz = s.size();
        if (sz == 0) return ans; 
        int i = 1;
        int j; 
        
        while (i<sz) {
            j = s.find_first_of('#', i);
            int len = stoi(s.substr(i, (j-i)));
            ans.push_back(s.substr(j+1, len));
            cout << "parse out: " <<  s.substr(j+1, len) << "\n";
            i = j + len + 2; 
        }
        
        return ans; 
    }
};

int main() {
  Codec codec; 
  vector<string> input = {"abc", "de", "float", "int", "for", "keyword", "923\t1"};
  string out = codec.encode(input);
  cout << out << "\n";

  cout << "decode:\n";
  auto words = codec.decode(out);
  for (auto & s : words) cout << s << "\n";
}
