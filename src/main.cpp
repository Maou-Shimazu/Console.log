// #define DOCTEST_CONFIG_IMPLEMENT
#include "../include/console_log.hpp"
// #include <doctest/doctest.h>
#include <iostream>

using namespace console;
using ll = log_level;

// TEST_CASE("formatting") {
//     std::string m{"words {yes}"};
//     CHECK(Format().formatter(m) == "yes");
// }

int main() {
    Console console1 = Console("logger1.log");
    for (auto i : cursed_range(0, 1000)) {
        console1.log("Information " + std::to_string(i));
    }
    Console console2 = Console("logger2.log");
    console2.log("Information ", cursed_range(0, 1000));

    log("Information", ll::Info);
    log("Warning", ll::Warning, std::cerr);
    log("Error", ll::Error, std::cerr);
    log("Success", ll::Success);
    log("Debug", ll::Debug);
    log("Default");
    log("Example of a long message with a custom color, Black.", ll::Info, std::cout, Black);

    // doctest::Context context;
    // context.run();

    return 0;
}
