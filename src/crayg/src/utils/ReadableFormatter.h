//
// Created by Jan on 24.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_UTILS_READABLEFORMATTER_H_
#define CRAYG_SRC_CRAYG_SRC_UTILS_READABLEFORMATTER_H_

#include <string>
#include <chrono>
class ReadableFormatter {
 public:
    std::string formatDuration(std::chrono::seconds seconds);
};

#endif //CRAYG_SRC_CRAYG_SRC_UTILS_READABLEFORMATTER_H_
