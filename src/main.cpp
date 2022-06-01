#include "console_log.hpp"
#include <iostream>
using namespace Console;
using ll = Console::log_level;

int main() {
    log("Information", ll::Info);
    log("Warning", ll::Warning);
    log("Error", ll::Error);
    log("Success", ll::Success);
    log("Default");
    log("Example of a very long message.", ll::Info, Black);
    return 0;
}
