//
// Created by jan on 27.12.18.
//

#ifndef CRAYG_REMAININGTIMECALCULATOR_H
#define CRAYG_REMAININGTIMECALCULATOR_H

#include <chrono>

class RemainingTimeCalculator {

 public:
    explicit RemainingTimeCalculator(std::chrono::steady_clock::time_point startTime);

    /**
     * Returns the remaining time for the given progress
     * @param progress progress in percent, for example 5
     * @return the remaining time in seconds
     */
    float getRemainingTimeByProgress(int progress);

 private:
    std::chrono::steady_clock::time_point startTime;
};

#endif //CRAYG_REMAININGTIMECALCULATOR_H
