//
// Created by Jan Honsbrok on 2019-08-11.
//

#include <fmt/format.h>
#include "KnipserAssertions.h"

namespace knipser {

BasicAssertion::BasicAssertion(const std::string &file, const int lineNumber) : file(file), lineNumber(lineNumber) {}

std::string BasicAssertion::createMessage(const std::string &assertionMessage) const {
    return fmt::format("{}:{}: Failure:\n{}", file, lineNumber, assertionMessage);
}

void BasicAssertion::doAssert(bool expression, const std::string &message) {
    if (!expression) {
        throw KnipserException(createMessage(message));
    }
}

ImageOutputExistsAssertion::ImageOutputExistsAssertion(const std::string &file, const int lineNumber) : BasicAssertion(
    file, lineNumber) {}

void ImageOutputExistsAssertion::doAssert(TestContext &testContext) {
    BasicAssertion::doAssert(testContext.imageOutputIsSet(),
                             "Image Output {} is not set!");

    const boost::filesystem::path &outputFilename = boost::filesystem::path(testContext.getOutputFilename());
    BasicAssertion::doAssert(exists(outputFilename),
                             fmt::format("Image Output {} does not exist!", testContext.getOutputFilename()));
}

bool ImageOutputExistsAssertion::exists(const boost::filesystem::path &path) const {
    return boost::filesystem::exists(path);
}

}


