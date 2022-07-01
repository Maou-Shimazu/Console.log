#include "../include/console_log.hpp"
#include <iostream>
using console::log;
using console::cursed_range;
using ll = log_level;

int main() {
    Console console1 = Console("logger1.log");
    for (auto i : cursed_range(0, 1000)) {
       console1.log("Information " + std::to_string(i));
    }
    Console console2 = Console("logger2.log");
    console2.log("Information ", cursed_range(0, 1000));
    
    log("Information", ll::Info);
    log("Warning", ll::Warning);
    log("Error", ll::Error);
    log("Success", ll::Success);
    log("Debug", ll::Debug);
    log("Default");
    log("Example of a long message with a custom color, Black.", ll::Info, Black);

    return 0;
}
