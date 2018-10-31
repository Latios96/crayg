//
// Created by Jan Honsbrok on 31.10.18.
//

#ifndef CRAYG_STOPWATCH_H
#define CRAYG_STOPWATCH_H

#include <chrono>
#include <iostream>

class StopWatch{
public:
    explicit StopWatch(std::string name) : name(name) {
        begin = std::chrono::steady_clock::now();
    }
    void end(){
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        std::cout << name << " took " << microseconds *0.0000006 << " seconds" << std::endl;
    };
private:
    std::chrono::steady_clock::time_point begin;
    std::string name;
};
#endif //CRAYG_STOPWATCH_H
