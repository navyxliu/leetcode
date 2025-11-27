#ifndef __STRING_HPP__
#define __STRING_HPP__
#include <vector>
#include <string>

std::vector<std::string> split(std::string s, const char* delimiters);
#if __cplusplus >= 202002L
#include <string_view>
using std::string_view;

std::vector<string_view>
split_view(const std::string& s, char delimiter);
#endif
#endif /*__STRING_HPP__*/