# libleetcode.a
**libleetcode** is C++ library for leetcoders. It consists of
1. Auxiliary functions and ADTs.
2. An io library: serialize/deserialize common ADTs of leetcode problems.
3. A debug macro that can pretty print a variable.
4. Some hacks that try to reduce the overhead of C++ runtime.

# Notes
My notes about data structure and algorithms.

# Build
```
$cmake -S . -B build
$cmake --build build
```

# Test
```
$cd build && ctest
```