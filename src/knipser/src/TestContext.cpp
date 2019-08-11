#include <utility>

//
// Created by jan on 03/08/2019.
//

#include "TestContext.h"
#include <boost/filesystem.hpp>

const std::string TestContext::getOutputFolder() const{
    return outputFolder;
}

const std::string TestContext::getOutputFilename(const std::string &nameWithExtension) const{
    return boost::filesystem::path(outputFolder)
            .append(nameWithExtension).string();
}

TestContext::TestContext(std::string outputFolder) : outputFolder(std::move(outputFolder)) {}
