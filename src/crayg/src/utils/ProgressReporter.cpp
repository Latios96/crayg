#include "ProgressReporter.h"
#include "crayg/foundation/strings/Humanize.h"

namespace crayg {

ProgressReporter::ProgressReporter(int maxIterations, std::function<void(int, float, float)> progressionCallback,
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
    std::function<void(int, float, float)> logProgress = [taskName](int progress, float timeElapsed,
                                                                    float timeRemaining) -> void {
        const auto formattedTimeElapsed =
            Humanize::naturalDuration(std::chrono::seconds(static_cast<int>(timeElapsed)));
        const auto formattedTimeRemaining =
            Humanize::naturalDuration(std::chrono::seconds(static_cast<int>(timeRemaining)));
        Logger::info("{} done by {}%, elapsed time: {}, remaining time: {}", taskName, progress, formattedTimeElapsed,
                     formattedTimeRemaining);
    };
    std::function<void(std::chrono::seconds)> finishCallback = [taskName](std::chrono::seconds seconds) -> void {
        Logger::info("{} took {}.", taskName, Humanize::naturalDuration(seconds));
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
            auto timeElapsed = std::chrono::steady_clock::now() - startTime;
            const float elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed).count();
            const float remainingTime = remainingTimeCalculator.getRemainingTimeByProgress(progress);
            progressionCallback(progress, elapsedTime, remainingTime);
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
