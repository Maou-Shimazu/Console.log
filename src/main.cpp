#include "../include/console_log.hpp"
#include <iostream>
using console::log;
using ll = log_level;

int main() {
    Console console = Console("logger.log");
    console.log("Information");
    log("Information", ll::Info);
    log("Warning", ll::Warning);
    log("Error", ll::Error);
    log("Success", ll::Success);
    log("Debug", ll::Debug);
    log("Default");
    log("Example of a long message with a custom color, Black.", ll::Info, Black);

    return 0;
}
