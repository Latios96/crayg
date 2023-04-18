#include "ProgressReporter.h"
#include "ReadableFormatter.h"

namespace crayg {

ProgressReporter::ProgressReporter(int maxIterations, std::function<void(int, float)> progressionCallback,
                                   std::function<void(std::chrono::seconds)> finishCallback)
    : maxIterations(maxIterations), progressionCallback(std::move(progressionCallback)),
      finishCallback(std::move(finishCallback)), iterationsDone(0),
      remainingTimeCalculator(std::chrono::steady_clock::now()) {
    startTime = std::chrono::steady_clock::now();
}

ProgressReporter::ProgressReporter(const ProgressReporter &progressReporter) {
    maxIterations = progressReporter.maxIterations;
    progressionCallback = progressReporter.progressionCallback;
    iterationsDone = progressReporter.iterationsDone.load();
    remainingTimeCalculator = progressReporter.remainingTimeCalculator;
    startTime = progressReporter.startTime;
}

ProgressReporter ProgressReporter::createLoggingProgressReporter(int maxIterations, const std::string &taskName) {
    std::function<void(int, float)> logProgress = [taskName](int progress, float timeRemaining) -> void {
        ReadableFormatter readableFormatter;
        readableFormatter.formatDuration(std::chrono::seconds(static_cast<int>(timeRemaining)));
        Logger::info("{} done by {}%, estimated time remaining: {}", taskName, progress,
                     readableFormatter.formatDuration(std::chrono::seconds(static_cast<int>(timeRemaining))));
    };
    std::function<void(std::chrono::seconds)> finishCallback = [taskName](std::chrono::seconds seconds) -> void {
        ReadableFormatter readableFormatter;
        Logger::info("{} took {}.", taskName, readableFormatter.formatDuration(seconds));
    };
    Logger::info("{}..", taskName);
    return {maxIterations, logProgress, finishCallback};
}

void ProgressReporter::iterationDone() {

    iterationsDone++;

    int newProgress = static_cast<int>(static_cast<float>(iterationsDone) / (static_cast<float>(maxIterations)) * 100);
    if (newProgress > progress) {
        progress = newProgress;
        if (progress % 1 == 0) {
            const float remainingTime = remainingTimeCalculator.getRemainingTimeByProgress(progress);
            progressionCallback(progress, remainingTime);
        }
    }
}

std::chrono::seconds ProgressReporter::finish() {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime);

    finishCallback(seconds);
    return seconds;
}

}
