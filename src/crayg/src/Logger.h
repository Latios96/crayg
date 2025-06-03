#pragma once

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define CRAYG_LOG_VALUE_INFO(val) Logger::info("{}: {}", #val, val);

namespace crayg {

class Logger {
  public:
    enum class LevelEnum { trace = 0, debug = 1, info = 2, warn = 3, err = 4, critical = 5, off = 6 };
    static void setLevel(LevelEnum level);

    template <typename... Args> inline static void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->trace(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args> inline static void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->debug(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args> inline static void info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->info(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args> inline static void warning(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->warn(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args> inline static void error(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->error(fmt, std::forward<Args>(args)...);
    }

    template <typename... Args> inline static void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::default_logger_raw()->critical(fmt, std::forward<Args>(args)...);
    }

    template <typename T> static void trace(const T &msg);

    template <typename T> static void debug(const T &msg);

    template <typename T> static void info(const T &msg);

    template <typename T> static void warning(const T &msg);

    template <typename T> static void critical(const T &msg);

    static void initialize();
    static void logToFile(const std::string &fileName);
    static void backtrace();
};

template <typename T> void Logger::trace(const T &msg) {
    spdlog::trace(msg);
}

template <typename T> void Logger::debug(const T &msg) {
    spdlog::debug(msg);
}

template <typename T> void Logger::info(const T &msg) {
    spdlog::info(msg);
}

template <typename T> void Logger::warning(const T &msg) {
    spdlog::warn(msg);
}

template <typename T> void Logger::critical(const T &msg) {
    spdlog::critical(msg);
}

}
