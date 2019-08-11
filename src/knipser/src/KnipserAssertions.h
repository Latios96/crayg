//
// Created by Jan Honsbrok on 2019-08-11.
//

#ifndef CRAYG_KNIPSERASSERTIONS_H
#define CRAYG_KNIPSERASSERTIONS_H

#include <string>
#include "TestContext.h"
#include <boost/filesystem.hpp>

class KnipserException : public std::exception {
public:
    explicit KnipserException(const std::string &message) : message(message) {}

    const char *what() const throw() {
        return "basic KnipserException";
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

#endif //CRAYG_KNIPSERASSERTIONS_H
