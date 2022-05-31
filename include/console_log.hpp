#pragma once

#ifndef CONSOLE_LOG_HPP
#define CONSOLE_LOG_HPP

#include <chrono>
#include <ctime>
#include <experimental/source_location>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

using std::experimental::source_location;

const std::string Black = "\u001b[30m";
const std::string Red = "\u001b[31m";
const std::string Green = "\u001b[32m";
const std::string Yellow = "\u001b[33m";
const std::string Blue = "\u001b[34m";
const std::string Magenta = "\u001b[35m";
const std::string Cyan = "\u001b[36m";
const std::string White = "\u001b[37m";
const std::string Reset = "\u001b[0m";

namespace Console {
    enum class log_level { Info, Warning, Error, Success };

    void time_now() {
        auto n = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(n);
        std::tm buf;
        localtime_s(&buf, &in_time_t);
        std::cout << std::put_time(&buf, "%Y-%m-%d %X");
    }

    template <class T>
    void log(T message, log_level log_level_ = log_level::Info, std::string color = Reset,
             std::experimental::source_location const source =
                 std::experimental::source_location::current()) {
        std::string _log_level;

        switch (log_level_) {
        case log_level::Info:
            _log_level = "Info";
            if (color == Reset) {
                color = Cyan;
            }
            break;
        case log_level::Warning:
            _log_level = "Warning";
            if (color == Reset) {
                color = Yellow;
            }
            break;
        case log_level::Error:
            _log_level = "Error";
            if (color == Reset) {
                color = Red;
            }
            break;
        case log_level::Success:
            _log_level = "Success";
            if (color == Reset) {
                color = Green;
            }
            break;
        }

        std::cout << color << "[" + _log_level + "] " << Reset;
        time_now();
        std::cout << " | ";
        std::cout
            << std::filesystem::path(source.file_name()).filename().string()
            << ":" << source.function_name() << ":" << source.line();
        std::cout << " | " << message << std::endl;
    }
}; // namespace Console

#endif