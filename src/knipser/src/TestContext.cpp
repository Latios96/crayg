#include <utility>

//
// Created by jan on 03/08/2019.
//

#include "TestContext.h"
#include <boost/filesystem.hpp>

const std::string TestContext::getOutputFolder() const {
    return outputFolder;
}

const std::string TestContext::getOutputFilename() const {
    return boost::filesystem::path(outputFolder)
            .append(imageOutputName).string();
}

TestContext::TestContext(std::string outputFolder) : outputFolder(std::move(outputFolder)) {}

void TestContext::setImageOutputName(const std::string &imageOutputName) {
    if (imageOutputSet) {
        throw std::logic_error("Can not set imageOutputName a second time!");
    }

    imageOutputSet = true;
    TestContext::imageOutputName = imageOutputName;



}



