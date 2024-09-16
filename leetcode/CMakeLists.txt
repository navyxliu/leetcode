add_library(leetcode io.cpp hack.cpp debug.cpp string.cpp)
set_property(TARGET leetcode PROPERTY CXX_STANDARD 20)
target_link_libraries(leetcode PUBLIC compiler_flags)
target_include_directories(leetcode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(test)