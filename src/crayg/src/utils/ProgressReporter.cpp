//
// Created by Jan Honsbrok on 11.11.18.
//

#include "ProgressReporter.h"
#include "ReadableFormatter.h"

namespace crayg {

ProgressReporter::ProgressReporter(int maxIterations, std::function<void(int, float)> progressionCallback) :
    maxIterations(maxIterations),
    progressionCallback(std::move(progressionCallback)),
    iterationsDone(0),
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
ProgressReporter ProgressReporter::createLoggingProgressReporter(int maxIterations, std::string logMessage) {
    std::function<void(int, float)> logProgress = [logMessage](int progress, float timeRemaining) -> void {
        ReadableFormatter readableFormatter;
        readableFormatter.formatDuration(std::chrono::seconds(static_cast<int>(timeRemaining)));
        Logger::info(logMessage.c_str(),
                     progress,
                     readableFormatter.formatDuration(std::chrono::seconds(static_cast<int>(timeRemaining))));
    };
    return {maxIterations, logProgress};
}
void ProgressReporter::iterationDone() {

    iterationsDone++;

    int newProgress = (int) ((float) iterationsDone) / ((float) maxIterations) * 100;
    if (newProgress > progress) {
        progress = newProgress;
        if (progress % 10 == 0) {
            const float remainingTime = remainingTimeCalculator.getRemainingTimeByProgress(progress);
            progressionCallback(progress, remainingTime);
        }
    }
}
void ProgressReporter::finish() {
    ReadableFormatter readableFormatter;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime);

    Logger::info("Rendering took {} seconds.", readableFormatter.formatDuration(seconds));
}

}
