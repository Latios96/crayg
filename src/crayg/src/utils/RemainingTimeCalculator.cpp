#include "RemainingTimeCalculator.h"

namespace crayg {

RemainingTimeCalculator::RemainingTimeCalculator(std::chrono::steady_clock::time_point startTime)
    : startTime{startTime} {
}

float RemainingTimeCalculator::getRemainingTimeByProgress(int progress) {
    const bool notStartedYet = progress == 0;
    const bool alreadyDone = progress == 100;

    if (notStartedYet) {
        return -1;
    }
    if (alreadyDone) {
        return 0;
    }
    const auto timeElapsed = getRemainingSecondsByProgress(progress);
    const auto timeElapsedInSeconds = std::chrono::duration_cast<std::chrono::seconds>(timeElapsed).count();
    const float secondsPerPercent = static_cast<float>(timeElapsedInSeconds) / static_cast<float>(progress);
    return secondsPerPercent * (100.0f - progress);
}

std::chrono::seconds RemainingTimeCalculator::getRemainingSecondsByProgress(int progress) {
    const bool notStartedYet = progress == 0;
    const bool alreadyDone = progress == 100;

    if (notStartedYet) {
        return std::chrono::seconds(-1);
    }
    if (alreadyDone) {
        return std::chrono::seconds(0);
    }

    auto timeElapsed = std::chrono::steady_clock::now() - startTime;
    return std::chrono::duration_cast<std::chrono::seconds>(timeElapsed);
}

RemainingTimeCalculator::RemainingTimeCalculator() = default;

}
