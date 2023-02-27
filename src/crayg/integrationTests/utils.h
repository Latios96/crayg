#ifndef CRAYG_SRC_CRAYG_INTEGRATIONTESTS_UTILS_H_
#define CRAYG_SRC_CRAYG_INTEGRATIONTESTS_UTILS_H_

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <string>

namespace crayg {

std::string getOutputFolder(const std::string &suiteName, const std::string &testName);

std::string getOutputFilename(const std::string &suiteName, const std::string &testName,
                              const std::string &extension = ".png");

} // namespace crayg

#endif // CRAYG_SRC_CRAYG_INTEGRATIONTESTS_UTILS_H_
