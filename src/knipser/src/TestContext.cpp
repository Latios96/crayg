#include <utility>

//
// Created by jan on 03/08/2019.
//

#include "TestContext.h"
#include <boost/filesystem.hpp>

std::string TestContext::getOutputFolder() const {
    return outputFolder;
}

std::string TestContext::getOutputFilename() const {
    return boost::filesystem::path(outputFolder)
        .append(imageOutputName).string();
}

TestContext::TestContext(std::string outputFolder, std::string referenceFolder) : outputFolder(std::move(outputFolder)),
                                                                                  referenceFolder(std::move(
                                                                                      referenceFolder)) {}

void TestContext::setImageOutputName(const std::string &imageOutputName) {
    if (imageOutputSet) {
        throw std::logic_error("Can not set imageOutputName a second time!");
    }

    imageOutputSet = true;
    TestContext::imageOutputName = imageOutputName;

}

bool TestContext::imageOutputIsSet() {
    return imageOutputSet;
}
std::string TestContext::getReferenceFolder() const {
    return referenceFolder;
}
std::string TestContext::getReferenceFilename() const {
    return boost::filesystem::path(referenceFolder)
        .append(imageOutputName).string();

}
bool TestContext::operator==(const TestContext &rhs) const {
    return outputFolder == rhs.outputFolder &&
        referenceFolder == rhs.referenceFolder;
}
bool TestContext::operator!=(const TestContext &rhs) const {
    return !(rhs == *this);
}



