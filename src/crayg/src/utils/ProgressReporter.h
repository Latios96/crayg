#include <utility>

//
// Created by Jan Honsbrok on 11.11.18.
//

#ifndef CRAYG_PROGRESSREPORTER_H
#define CRAYG_PROGRESSREPORTER_H

#include <functional>
#include "RemainingTimeCalculator.h"
#include "Logger.h"

class ProgressReporter {
 public:
    ProgressReporter(int maxIterations, std::function<void(int, float)> progressionCallback);
    ProgressReporter(const ProgressReporter &progressReporter);

    static ProgressReporter createLoggingProgressReporter(int maxIterations, std::string logMessage);

    void iterationDone();

    void finish();

    std::atomic<int> iterationsDone = {0};
 private:
    int maxIterations;
    int progress = 0;
    std::function<void(int, float)> progressionCallback;
    std::chrono::steady_clock::time_point startTime;
    RemainingTimeCalculator remainingTimeCalculator;
};

#endif //CRAYG_PROGRESSREPORTER_H
