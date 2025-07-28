#pragma once

#include <stdexcept>
#include <string>

namespace crayg {

class InvalidLensFileException : public std::runtime_error {
  public:
    explicit InvalidLensFileException(const std::string &message);
    InvalidLensFileException(int lineIndex, const std::string &message);
};

class LensFileParseUtils {
  public:
    static float parseFloat(int lineIndex, const std::string &floatStr, const std::string &name);
    static int parseInt(int lineIndex, const std::string &intStr, const std::string &name);
};

}