//
// Created by Jan on 22.11.2020.
//

#include "Preconditions.h"

namespace crayg {

FailureInformation::FailureInformation(const std::string &file, int line) : file(file), line(line) {}

}