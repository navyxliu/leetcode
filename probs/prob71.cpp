#include <vector>
#include <string>
#include <iostream>
using namespace std; 

class Solution {
public:
    string simplifyPath(string s) {
        vector<string> comps; 
        int sz = s.size();
        if (sz == 0) return "";
        else if (sz == 1) return "/";
        else if (s[sz-1] != '/') {
            s = s + "/";
        }
        
        int i = 1; 
        int j = s.find_first_of('/', i);
        comps.push_back("");
        
        while (i < sz && j != string::npos) {
            string t = s.substr(i, (j-i));
            cout << t << "\n";
            
            if (t == "..") {
                if (comps.size() == 1) {
                    return "/";
                }
                else {
                    comps.pop_back();
                }
            }
            else if (t == ".");
            else comps.push_back(t);
            
            i = j;
            while (i < sz && s[i] == '/') 
                i++;
                
            j = s.find_first_of('/', i);
        }
        
        sz = comps.size();
        if (sz == 1) return "/";
        
        stringstream ss; 
        for (int i=0; i<sz; ++i) {
            ss << comps[i]; 
            if (i != sz-1) ss << "/";
        }
        
        return ss.str(); 
    }
};

int main() {

}
