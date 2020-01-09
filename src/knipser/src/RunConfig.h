//
// Created by Jan Honsbrok on 2019-08-11.
//

#ifndef CRAYG_RUNCONFIG_H
#define CRAYG_RUNCONFIG_H

#include <string>
#include <vector>
#include "TestPattern.h"

class RunConfig {
 public:
    RunConfig(std::string outputFolder, std::string referenceFolder);
    RunConfig(std::string outputFolder, std::string referenceFolder, std::vector<TestPattern> testPatterns);

    const std::string outputFolder;
    const std::string referenceFolder;
    const std::vector<TestPattern> testPatterns;
};

#endif //CRAYG_RUNCONFIG_H
