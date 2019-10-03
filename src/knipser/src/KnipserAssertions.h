//
// Created by Jan Honsbrok on 2019-08-11.
//

#ifndef CRAYG_KNIPSERASSERTIONS_H
#define CRAYG_KNIPSERASSERTIONS_H

#include <string>
#include "TestContext.h"
#include "ImageComparator.h"
#include <boost/filesystem.hpp>
#include <fmt/format.h>

class KnipserException : public std::exception {
 public:
    explicit KnipserException(const std::string &message) : message(message) {}

    const char *what() const throw() {
        return message.c_str();
    }

 private:
    std::string message;
};

class BasicAssertion {
 public:
    BasicAssertion(const std::string &file, const int lineNumber);

    std::string createMessage(const std::string &assertionMessage) const;

    void doAssert(bool expression, const std::string &message);

 protected:
    const std::string file;
    const int lineNumber;
};

class ImageOutputExistsAssertion : public BasicAssertion {
 public:
    ImageOutputExistsAssertion(const std::string &file, const int lineNumber);

    void doAssert(TestContext &testContext);

 protected:
    virtual bool exists(const boost::filesystem::path &path) const;
};
template<typename T>
class ImagesAreEqualAssertion : public BasicAssertion {
 public:
    ImagesAreEqualAssertion(const std::string &file, const int lineNumber) : BasicAssertion(file,
                                                                                            lineNumber) {

    }

    void doAssert(const TestContext &testContext) {
        T imageComparator(testContext.getReferenceFilename(), testContext.getOutputFilename());
        ImageComparatorResult result = imageComparator.compareImages();
        BasicAssertion::doAssert(!result.isError(),
                                 fmt::format("Images {} and {} are not equal!!!",
                                             testContext.getReferenceFilename(),
                                             testContext.getOutputFilename()));
    }
};

#define ASSERT_IMAGES_ARE_EQUAL(context) ImagesAreEqualAssertion<OpenImageIoImageComparator> imagesAreEqualAssertion(__FILE__, __LINE__); \
BasicAssertion referenceImageExists(__FILE__, __LINE__); \
referenceImageExists.doAssert(boost::filesystem::exists(context.getReferenceFilename()), fmt::format("Reference image {} does not exist!", context.getReferenceFilename())); \
BasicAssertion outputFileNameExists(__FILE__, __LINE__); \
outputFileNameExists.doAssert(boost::filesystem::exists(context.getOutputFilename()), fmt::format("Output image {} does not exist!", context.getOutputFilename())); \
imagesAreEqualAssertion.doAssert(context);

#endif //CRAYG_KNIPSERASSERTIONS_H
