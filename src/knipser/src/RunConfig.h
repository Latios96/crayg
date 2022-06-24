#ifndef CRAYG_RUNCONFIG_H
#define CRAYG_RUNCONFIG_H

#include <string>
#include <vector>
#include "TestPattern.h"

namespace knipser {

class RunConfig {
 public:
    RunConfig(std::string outputFolder, std::string referenceFolder);
    RunConfig(std::string outputFolder, std::string referenceFolder, std::vector<TestPattern> testPatterns);

    const std::string outputFolder;
    const std::string referenceFolder;
    const std::vector<TestPattern> testPatterns;
};

}

#endif //CRAYG_RUNCONFIG_H
