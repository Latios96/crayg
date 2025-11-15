#include "StopWatch.h"
#include "crayg/foundation/strings/Humanize.h"
#include "fmt/chrono.h"
#include <spdlog/spdlog.h>

#include "fmt/format.h"
#include "fmt/std.h"

#include <utility>

namespace crayg {

StopWatch::StopWatch(std::string name, std::function<void(std::string)> outputCallback,
                     StopWatchReportFormat reportFormat)
    : name(std::move(name)), outputCallback(outputCallback), reportFormat(reportFormat) {
    begin = std::chrono::steady_clock::now();
}

StopWatch::StopWatch(std::string name, StopWatchReportFormat reportFormat)
    : StopWatch(
          name, [](std::string message) -> void { spdlog::info("{}", message); }, reportFormat) {
}

void StopWatch::end() {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (reportFormat == StopWatchReportFormat::SECONDS) {
        const std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
        outputCallback(fmt::format("{} took {:.2}.", name, seconds));
    } else if (reportFormat == StopWatchReportFormat::MILLISECONDS) {
        const std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
        outputCallback(fmt::format("{} took {:.2}.", name, milliseconds));
    } else {
        const std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
        outputCallback(fmt::format("{} took {}.", name, Humanize::naturalDuration(seconds)));
    }
}

ScopedStopWatch::ScopedStopWatch(const std::string &name, StopWatchReportFormat reportFormat)
    : stopWatch(name, reportFormat) {
}

ScopedStopWatch::~ScopedStopWatch() {
    stopWatch.end();
}
}