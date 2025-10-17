#pragma once

#include <chrono>
#include <functional>

namespace crayg {

class StopWatch {
  public:
    explicit StopWatch(std::string name, std::function<void(std::string)> outputCallback);

    static StopWatch createStopWatch(std::string name);

    void end();

  private:
    std::chrono::steady_clock::time_point begin;
    std::string name;
    std::function<void(std::string)> outputCallback;
};

class ScopedStopWatch {
  public:
    explicit ScopedStopWatch(const std::string &name);

    virtual ~ScopedStopWatch();

  private:
    StopWatch stopWatch;
};

class InformativeScopedStopWatch : public ScopedStopWatch {
  public:
    explicit InformativeScopedStopWatch(const std::string &name);
};

}
