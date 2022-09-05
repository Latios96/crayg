#ifndef CRAYG_STOPWATCH_H
#define CRAYG_STOPWATCH_H

#include <chrono>
#include <iostream>
#include <spdlog/spdlog.h>

#include "fmt/format.h"
#include "Logger.h"
#include <utility>

namespace crayg {

class StopWatch {
 public:

    explicit StopWatch(std::string name, std::function<void(std::string)> outputCallback) :
        name(std::move(name)),
        outputCallback(outputCallback) {
        begin = std::chrono::steady_clock::now();
    }

    static StopWatch createStopWatch(std::string name) {
        std::function<void(std::string)> callback = [](std::string message) -> void {
            Logger::info(message.c_str());
        };
        return StopWatch(name, callback);
    }

    void end() {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        outputCallback(fmt::format("{} took {:.2f} seconds.", name, microseconds * 0.0000006));
    };
 private:
    std::chrono::steady_clock::time_point begin;
    std::string name;
    std::function<void(std::string)> outputCallback;
};

class ScopedStopWatch {
 public:
    explicit ScopedStopWatch(const std::string &name) : stopWatch(StopWatch::createStopWatch(name)) {
    }
    virtual ~ScopedStopWatch() {
        stopWatch.end();
    }
 private:
    StopWatch stopWatch;
};

class InformativeScopedStopWatch : public ScopedStopWatch {
 public:
    explicit InformativeScopedStopWatch(const std::string &name) : ScopedStopWatch(name) {
        Logger::info("{}..", name);
    }
};

}
#endif //CRAYG_STOPWATCH_H
