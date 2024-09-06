#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#define dbg (std::cout)

// forward declaration
class TreeNode;

#define PRINT(var) \
    dbg << #var << " = " << pp(var) << '\n';

template <class T>
const T& pp(const T& t) {
    return t;
}

template <class T>
std::string pp(const std::vector<T>& vec) {
    std::stringstream ss;
    bool first = true;
    ss << "[" ;
    for (auto &e: vec) {
        if (!first) {
            ss << ",";
        } else {
            first = false;
        }
        ss << pp(e);
    }
    ss << "]";
    return ss.str();
}

#endif // __DEBUG_HPP__