#include "leetcode.hpp"
#include "debug.hpp"

void test_primitives() {
    int foo = 1;
    PRINT(foo) // skip comma is acceptable

    const double pi = 3.1415926;
    PRINT(pi) // skip comma is acceptable
}

void test_vector() {
    vector<int> empty;
    PRINT(empty);

    vector<int> vec = {1,2,3,4,5};
    PRINT(vec);

    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    PRINT(dirs);
}

int main() {
    test_primitives();

    string bar = "hello";
    PRINT(bar);

    test_vector();
}