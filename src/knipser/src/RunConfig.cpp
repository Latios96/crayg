//
// Created by Jan Honsbrok on 2019-08-11.
//

#include "RunConfig.h"

#include <utility>

RunConfig::RunConfig(std::string outputFolder, std::string referenceFolder)
    : outputFolder(std::move(outputFolder)), referenceFolder(std::move(referenceFolder)) {}

RunConfig::RunConfig(std::string outputFolder, std::string referenceFolder, std::vector<TestPattern> testPatterns)
    : outputFolder(std::move(outputFolder)),
      referenceFolder(std::move(referenceFolder)),
      testPatterns(std::move(testPatterns)) {}

