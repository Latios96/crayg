#ifndef CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_

#include <string>
#include <ostream>

namespace knipser {

class TestContext {
 public:
    explicit TestContext(std::string outputFolder, std::string referenceFolder);

    void setImageOutputName(const std::string &imageOutputName);
    bool imageOutputIsSet() const;

    std::string getOutputFolder() const;
    std::string getOutputFilename() const;

    std::string getReferenceFolder() const;
    std::string getReferenceFilename() const;

    bool operator==(const TestContext &rhs) const;
    bool operator!=(const TestContext &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const TestContext &context);
 private:
    const std::string outputFolder;
    const std::string referenceFolder;
    std::string imageOutputName;
    bool imageOutputSet = false;
};

}

#endif //CRAYG_SRC_KNIPSER_SRC_TESTCONTEXT_H_
