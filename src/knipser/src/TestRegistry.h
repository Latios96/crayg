//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_
#define CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_

#include <memory>
#include <vector>
#include "TestContext.h"
#include "KnipserTest.h"

#define KNIPSER_REGISTER_TEST(name, lambda)\
bool testRegistrationResult_##name = TestRegistry::getInstance()->registerTest(KnipserTest(std::string(#name), lambda));

class TestRegistry {
 public:
    static std::shared_ptr<TestRegistry> &getInstance();
    static void setInstance(const std::shared_ptr<TestRegistry> &instance);
    bool registerTest(const KnipserTest &knipserTest);
    const std::vector<KnipserTest> &getTests() const;
 private:
    static std::shared_ptr<TestRegistry> instance;
    std::vector<KnipserTest> tests;
};

#endif //CRAYG_SRC_KNIPSER_SRC_TESTREGISTRY_H_
