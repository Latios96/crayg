#pragma once

#include <chrono>

namespace crayg {

class RemainingTimeCalculator {

  public:
    RemainingTimeCalculator();
    explicit RemainingTimeCalculator(std::chrono::steady_clock::time_point startTime);

    float getRemainingTimeByProgress(int progress);
    std::chrono::seconds getRemainingSecondsByProgress(int progress);

  private:
    std::chrono::steady_clock::time_point startTime;
};

}
