#ifndef CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_

#include <vector>
#include "TestContext.h"
#include "KnipserTest.h"

namespace knipser {

class TestRegistry {
 public:
    bool registerTest(const KnipserTest &knipserTest);
    TestRegistry &registerTests(const std::vector<KnipserTest> &knipserTests);
    const std::vector<KnipserTest> &getTests() const;
 private:
    std::vector<KnipserTest> tests;
};

}

#endif //CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_
