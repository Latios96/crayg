#include <utility>

//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_STOPWATCH_H
#define CRAYG_STOPWATCH_H

#include <chrono>
#include <iostream>
#include <spdlog/spdlog.h>

#define FMT_HEADER_ONLY
#include "fmt/format.h"

class StopWatch{
public:

    explicit StopWatch(std::string name, std::function<void(std::string)> outputCallback) :
    name(std::move(name)),
    outputCallback(outputCallback){
        begin = std::chrono::steady_clock::now();
    }

    static StopWatch createStopWatch(std::string name){
        std::function<void(std::string)> callback = [] (std::string message) -> void {
            spdlog::get("console")->info(message.c_str());
        };
        return StopWatch(name, callback);
    }

    void end(){
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        outputCallback(fmt::format("{} took {} seconds.", name, microseconds *0.0000006));
    };
private:
    std::chrono::steady_clock::time_point begin;
    std::string name;
    std::function<void(std::string)> outputCallback;
};
#endif //CRAYG_STOPWATCH_H
