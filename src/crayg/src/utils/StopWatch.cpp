#include "StopWatch.h"
#include <iostream>
#include <spdlog/spdlog.h>

#include "Logger.h"
#include "ReadableFormatter.h"
#include "fmt/format.h"
#include <utility>

namespace crayg {

StopWatch::StopWatch(std::string name, std::function<void(std::string)> outputCallback)
    : name(std::move(name)), outputCallback(outputCallback) {
    begin = std::chrono::steady_clock::now();
}

StopWatch StopWatch::createStopWatch(std::string name) {
    std::function<void(std::string)> callback = [](std::string message) -> void { Logger::info(message.c_str()); };
    return StopWatch(name, callback);
}

void StopWatch::end() {
    ReadableFormatter readableFormatter;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);

    outputCallback(fmt::format("{} took {}.", name, readableFormatter.formatDuration(std::chrono::seconds(seconds))));
}

ScopedStopWatch::ScopedStopWatch(const std::string &name) : stopWatch(StopWatch::createStopWatch(name)) {
}

ScopedStopWatch::~ScopedStopWatch() {
    stopWatch.end();
}

InformativeScopedStopWatch::InformativeScopedStopWatch(const std::string &name) : ScopedStopWatch(name) {
    Logger::info("{}..", name);
}

}