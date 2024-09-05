cmake_minimum_required(VERSION 3.10)
project(Leetcode)

add_executable(prob129 sum_root_to_leaf_num.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("leetcode")
target_link_libraries(prob129 PUBLIC leetcode)
target_include_directories(prob129 PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/leetcode"
                          )