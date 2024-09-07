#include <iostream>
#include <ostream>

std::ostream* __dbg = nullptr;

void set_dbg(std::ostream& console) {
    __dbg = &console;
}
void reset_dbg() {
    __dbg = nullptr;
}
