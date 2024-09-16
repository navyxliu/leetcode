add_executable(
  test_debug
  test_debug.cpp
)
target_link_libraries(
  test_debug PUBLIC
  leetcode
  GTest::gtest_main
)

add_executable(
  test_string
  test_string.cpp
)
set_property(TARGET test_string PROPERTY CXX_STANDARD 20)
target_link_libraries(
  test_string PUBLIC
  leetcode
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_debug)
gtest_discover_tests(test_string)
