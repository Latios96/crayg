#include "utils.h"

std::string crayg::getOutputFolder(const std::string &suiteName, const std::string &testName) {
    const auto folder = boost::filesystem::path("result") / suiteName / testName;
    boost::filesystem::create_directories(folder);
    return folder.string();
}

std::string crayg::getOutputFilename(const std::string &suiteName, const std::string &testName,
                                     const std::string &extension) {
    return (boost::filesystem::path(getOutputFolder(suiteName, testName)) / (testName + extension)).string();
}
