#pragma once

#include <string>

namespace crayg {

std::string getOutputFolder(const std::string &suiteName, const std::string &testName);

std::string getOutputFilename(const std::string &suiteName, const std::string &testName,
                              const std::string &extension = ".png");

}
