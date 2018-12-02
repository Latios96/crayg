#include <utility>

//
// Created by Jan Honsbrok on 11.11.18.
//

#ifndef CRAYG_PROGRESSREPORTER_H
#define CRAYG_PROGRESSREPORTER_H


#include <functional>
#include <spdlog/spdlog.h>
#define FMT_HEADER_ONLY
#include "fmt/format.h"

// todo add time remaining
class ProgressReporter{
public:
    ProgressReporter(int maxIterations, std::function<void(int)> progressionCallback) : maxIterations(
            maxIterations), progressionCallback(std::move(progressionCallback)), iterationsDone(0) {
        startTime = std::chrono::steady_clock::now();
    }

    static ProgressReporter createLoggingProgressReporter(int maxIterations, std::string logMessage){
        std::function<void(int)> logProgress = [logMessage] (int progress) -> void {
            spdlog::get("console")->info(logMessage.c_str(), progress);
        };
        return {maxIterations, logProgress};
    }

    void iterationDone(){

        iterationsDone++;

        int newProgress = (int) ((float) iterationsDone) / ((float) maxIterations) * 100;
        if (newProgress > progress){
            progress = newProgress;
            if(progress % 10 == 0){
                progressionCallback(progress);
            }
        }
    }

    void finish(){
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - startTime).count();

        spdlog::get("console")->info("Rendering took {} seconds.", microseconds *0.0000006);
    }

    int iterationsDone;
private:
    int maxIterations;
    int progress;
    std::function<void(int)> progressionCallback;
    std::chrono::steady_clock::time_point startTime;
};


#endif //CRAYG_PROGRESSREPORTER_H
