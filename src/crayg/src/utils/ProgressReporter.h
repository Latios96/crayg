#ifndef CRAYG_PROGRESSREPORTER_H
#define CRAYG_PROGRESSREPORTER_H

#include <functional>
#include "RemainingTimeCalculator.h"
#include "Logger.h"
#include <utility>

namespace crayg {

class ProgressReporter {
 public:
    ProgressReporter(int maxIterations, std::function<void(int, float)> progressionCallback,std::function<void(std::chrono::seconds)> finishCallback);
    ProgressReporter(const ProgressReporter &progressReporter);

    static ProgressReporter createLoggingProgressReporter(int maxIterations, const std::string &taskName);

    void iterationDone();

    std::chrono::seconds finish();

    std::atomic<int> iterationsDone = {0};
 private:
    int maxIterations;
    int progress = 0;
    std::function<void(int, float)> progressionCallback;
    std::function<void(std::chrono::seconds)> finishCallback;
    std::chrono::steady_clock::time_point startTime;
    RemainingTimeCalculator remainingTimeCalculator;
};

}

#endif //CRAYG_PROGRESSREPORTER_H
