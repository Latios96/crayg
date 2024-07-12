#include "utils.h"
#include "filesystem"

std::string crayg::getOutputFolder(const std::string &suiteName, const std::string &testName) {
    const auto folder = std::filesystem::path("result") / suiteName / testName;
    std::filesystem::create_directories(folder);
    return folder.string();
}

std::string crayg::getOutputFilename(const std::string &suiteName, const std::string &testName,
                                     const std::string &extension) {
    return (std::filesystem::path(getOutputFolder(suiteName, testName)) / (testName + extension)).string();
}
