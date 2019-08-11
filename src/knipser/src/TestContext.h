//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_

#include <string>

class TestContext {
public:
    explicit TestContext(std::string outputFolder);

    void setImageOutputName(const std::string &imageOutputName);

    const std::string getOutputFolder() const;
    const std::string getOutputFilename() const;

private:
    const std::string outputFolder;
    std::string imageOutputName;
    bool imageOutputSet = false;

};

#endif //CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
