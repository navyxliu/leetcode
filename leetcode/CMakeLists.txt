add_library(leetcode io.cpp hack.cpp debug.cpp)
target_link_libraries(leetcode PUBLIC compiler_flags)
target_include_directories(leetcode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)