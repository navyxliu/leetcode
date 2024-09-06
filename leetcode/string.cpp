#include "string.hpp"

std::vector<std::string> 
split(std::string s, const char* delimiters) {
    std::vector<std::string> ans;
    size_t p = 0;
    size_t next = s.find_first_of(delimiters);

    while (next != std::string::npos) {
        if (p < next) {
            ans.push_back(s.substr(p, next - p));
        }
        p = next + 1;
        next = s.find_first_of(delimiters, p);
    }

    if (p < s.length()) {
        ans.push_back(s.substr(p));
    }
    return ans;
}