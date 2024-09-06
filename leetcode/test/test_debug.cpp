#include "../leetcode.hpp"
#include "../debug.hpp"

#include <gtest/gtest.h>

class DebugTest : public testing::Test {
    stringstream ss; 

public:
    DebugTest() {
        set_dbg(ss);
    }

    ~DebugTest() {
        reset_dbg();
    }

    string getOutput() {
        string line;
        std::getline(ss, line);
        return line;
    }
};

TEST_F(DebugTest, primitives) {
    int foo = 1;
    PRINT(foo) // skip comma is acceptable
    ASSERT_EQ(getOutput(), "foo = 1");

    const double pi = 3.14159;
    PRINT(pi) // skip comma is acceptable
    ASSERT_EQ(getOutput(), "pi = 3.14159");
}

TEST_F(DebugTest, string) {
    string bar = "hello";
    PRINT(bar);
    ASSERT_EQ(getOutput(), "bar = hello");
}

TEST_F(DebugTest, vector) {
    vector<int> empty;
    PRINT(empty);
    ASSERT_EQ(getOutput(), "empty = []");

    vector<int> vec = {1,2,3,4,5};
    PRINT(vec);
    ASSERT_EQ(getOutput(), "vec = [1,2,3,4,5]");

    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    PRINT(dirs);
    ASSERT_EQ(getOutput(), "dirs = [[1,0],[0,1],[-1,0],[0,-1]]");
}