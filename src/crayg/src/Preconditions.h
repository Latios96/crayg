//
// Created by Jan on 22.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
#define CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_

#include <stdexcept>
#include <fmt/format.h>
#include <basics/Vector3f.h>
#include "Logger.h"

#ifdef _DEBUG
#define SKIP_IF_DISABLED
#else
#define SKIP_IF_DISABLED
#endif

struct FailureInformation {
    std::string file;
    int line;
    FailureInformation(const std::string &file, int line);
};

#define FAILURE_INFORMATION FailureInformation(__FILE__, __LINE__)

class Preconditions {

 public:
    static void checkArgument(bool expression, const FailureInformation &failureInformation) {
        SKIP_IF_DISABLED;
        checkArgument(expression, "Expression failed!", failureInformation);
    }
    static void checkArgument(bool expression,
                              const std::string &exrStr,
                              const FailureInformation &failureInformation) {
        SKIP_IF_DISABLED;
        if (!expression) {
            fail(exrStr, failureInformation);
        }
    }
    static void checkIsUnitVector(const Vector3f &vector3f, const FailureInformation &failureInformation) {
        SKIP_IF_DISABLED;
        checkArgument(vector3f.length() == 1, fmt::format("Vector is not unit vector!: {} {} {}",
                                                          vector3f.x,
                                                          vector3f.y,
                                                          vector3f.z), failureInformation);
    }
 private:
    static void fail(const std::string &message, const FailureInformation &failureInformation) {
        auto formattedMessage = fmt::format("{}, at {} {}",
                                            message,
                                            failureInformation.file,
                                            failureInformation.line);
        Logger::error(formattedMessage.c_str());
        throw std::invalid_argument(formattedMessage);
    }
};

#endif //CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
