#pragma once
#ifndef CONSOLE_LOG_HPP
#define CONSOLE_LOG_HPP

#include <chrono>
#include <ctime>
#include <experimental/source_location>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::experimental::source_location;

const std::string Black     = "\u001b[30m";
const std::string Red       = "\u001b[31m";
const std::string Green     = "\u001b[32m";
const std::string Yellow    = "\u001b[33m";
const std::string Blue      = "\u001b[34m";
const std::string Magenta   = "\u001b[35m";
const std::string Cyan      = "\u001b[36m";
const std::string White     = "\u001b[37m";
const std::string Reset     = "\u001b[0m";
const std::string Underline = "\u001b[4m";

enum class log_level : char {
    Info    = '-',
    Warning = '!',
    Error   = 'X',
    Success = '+',
    Debug   = '?'
};
namespace console {
    std::vector<size_t> cursed_range(size_t x, size_t y) {
        std::vector<size_t> result;
        for (; x <= y; x++) {
            result.push_back(x);
        }
        return result;
    }
    template <typename T> auto consume(T v) { return v; }
} // namespace console

// TODO: shift formatting options from log to this class.
class Format {
  public:
    Format() = default;
    auto formatter(std::string content) {
        std::string current, end, str;
        for (auto i = 0; i <= content.length(); i++) {
            current = content.at(i);     // current character
            end     = content.at(i + 1); // next character
            while (current == "{" && end != "}") {
                current += content.at(i);
                str += current;
                i++;
            }
        }
        return current;
    }
    template <typename T> static auto default_format(T content) {
        return content;
    }
};

class Console {
  private:
    std::string fileH;

  public:
    Console() = default;
    explicit Console(std::string file) : fileH(std::move(file)) {
        if (!std::filesystem::exists(this->fileH))
            std::ofstream ost(this->fileH);
    }
    template <typename T> Console* log(T message, Format formatter = Format()) {
        std::thread thread([this, formatter, message]() {
            std::ofstream ost(this->fileH, std::ios::app);
            ost << formatter.default_format(message) << "\n";
        });
        thread.join();
        return this;
    }
    template <typename T>
    Console* log(T message, std::vector<size_t> range,
                 Format formatter = Format()) {
        std::thread thread([this, formatter, message, range]() {
            for (auto i : range) {
                std::ofstream ost(this->fileH, std::ios::app);
                ost << formatter.default_format(message) << "\n";
                console::consume(i); // to ignore unused variable warnings
            }
        });
        thread.join();
        return this;
    }
}; // class Console
namespace console {
    inline void time_now() {
        auto now             = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::tm tn           = *std::localtime(&end_time);
        std::cout << std::put_time(&tn, "%X");
    }

    template <class T>
    static void log(T message, log_level log_level_ = log_level::Info,
                    std::string color            = Reset,
                    source_location const source = source_location::current()) {
        switch (log_level_) {
        case log_level::Info:
            if (color == Reset) color = Cyan;
            break;
        case log_level::Warning:
            if (color == Reset) color = Yellow;
            break;
        case log_level::Error:
            if (color == Reset) color = Red;
            break;
        case log_level::Success:
            if (color == Reset) color = Green;
            break;
        case log_level::Debug:
            if (color == Reset) color = Magenta;
            break;
        }

        std::cout << color << "[" << static_cast<char>(log_level_) << "] ";
        time_now();
        std::cout << " || " << Reset;
        std::cout
            << std::filesystem::path(source.file_name()).filename().string()
            << ":" << source.function_name() << ":" << source.line() << Reset;
        std::cout << color << " || " << Reset << message << std::endl;
    }
} // namespace console

#endif
