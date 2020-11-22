//
// Created by Jan on 22.11.2020.
//

#ifndef CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
#define CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_

#include <stdexcept>
#include <fmt/format.h>
#include <basics/Vector3f.h>
#include "Logger.h"

class Preconditions {

 public:
    static void checkArgument(bool expression) {
        if (!expression) {
            fail(fmt::format("Expression failed"));
        }
    }
    static void checkArgument(bool expression, const std::string &exrStr) {
        if (!expression) {
            fail(exrStr);
        }
    }
    static void checkIsUnitVector(const Vector3f &vector3f) {
        if (vector3f.length() != 1) {
            fail(fmt::format("Vector is not unit vector!: {} {} {}",
                             vector3f.x,
                             vector3f.y,
                             vector3f.z));
        }
    }
 private:
    static void fail(const std::string &message) {
        Logger::error(message.c_str());
        throw std::invalid_argument(message);
    }
};

#endif //CRAYG_SRC_CRAYG_SRC_PRECONDITIONS_H_
