//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_

#include <string>

class TestContext {
public:
    TestContext(std::string outputFolder);

    const std::string getOutputFolder() const;
    const std::string getOutputFilename(const std::string &nameWithExtension) const;

private:
    const std::string outputFolder;
};

#endif //CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
