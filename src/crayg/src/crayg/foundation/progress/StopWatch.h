#pragma once

#include <chrono>
#include <functional>

namespace crayg {

enum class StopWatchReportFormat { HUMAN, SECONDS, MILLISECONDS };

class StopWatch {
  public:
    StopWatch(std::string name, std::function<void(std::string)> outputCallback, StopWatchReportFormat reportFormat);

    StopWatch(std::string name, StopWatchReportFormat reportFormat = StopWatchReportFormat::HUMAN);

    void end();

  private:
    std::chrono::steady_clock::time_point begin;
    std::string name;
    std::function<void(std::string)> outputCallback;
    StopWatchReportFormat reportFormat;
};

class ScopedStopWatch {
  public:
    explicit ScopedStopWatch(const std::string &name,
                             StopWatchReportFormat reportFormat = StopWatchReportFormat::HUMAN);

    virtual ~ScopedStopWatch();

  private:
    StopWatch stopWatch;
};

}