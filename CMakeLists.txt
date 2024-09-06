cmake_minimum_required(VERSION 3.15)
project(Leetcode)

# dependencies
## add gtest: https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#stdcxx
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>"
)

#libleetcode
add_subdirectory("leetcode")

# executable
add_executable(prob129 probs/sum_root_to_leaf_num.cpp)
target_link_libraries(prob129 PUBLIC leetcode compiler_flags)
target_include_directories(prob129 PUBLIC
                          "${PROJECT_BINARY_DIR}")
