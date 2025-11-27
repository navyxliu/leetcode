#include "string.hpp"

std::vector<std::string> 
split(std::string s, const char* delimiters) {
    std::vector<std::string> ans;
    size_t p = 0;
    size_t next = s.find_first_of(delimiters);

    while (next != std::string::npos) {
        ans.push_back(s.substr(p, next - p));
        p = next + 1;
        next = s.find_first_of(delimiters, p);
    }

    ans.push_back(s.substr(p));
    return ans;
}
#if __cplusplus >= 202002L
#include <ranges>

std::vector<string_view>
split_view(const std::string& s, char delimiter) {
    std::vector<string_view> ans;
    for (const auto &sub: string_view{s} | std::ranges::views::split(delimiter)) {
        ans.push_back(string_view{sub.begin(), sub.end()});
    }
    return ans;
}
#endif
