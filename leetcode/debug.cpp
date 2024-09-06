#include <iostream>
#include <ostream>

std::ostream* dbg = &std::cout;

void set_dbg(std::ostream& console) {
    dbg = &console;
}
void reset_dbg() {
    dbg = &std::cout;
}
