#include "../string.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(StringTest, simple) {
    string ipv4 = "192.168.0.1";
    vector<string> addrs = split(ipv4, ".");
    ASSERT_EQ(addrs.size(), 4);
    ASSERT_EQ(addrs, vector<string>({"192", "168", "0", "1"}));

    string msg = "hello,,world!";
    vector<string> words = split(msg, ",!");
    ASSERT_EQ(words.size(), 2);
    ASSERT_EQ(words, vector<string>({"hello", "world"}));

    msg = "helloworld";
    words = split(msg, ".!");
    ASSERT_EQ(words.size(), 1);
    ASSERT_EQ(words[0], "helloworld");
}