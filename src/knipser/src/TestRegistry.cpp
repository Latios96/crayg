//
// Created by jan on 03/08/2019.
//

#include <vector>
#include "TestRegistry.h"

namespace knipser {

const std::vector<KnipserTest> &TestRegistry::getTests() const {
    return tests;
}
bool TestRegistry::registerTest(const KnipserTest &knipserTest) {
    tests.push_back(knipserTest);
    return true;
}
TestRegistry &TestRegistry::registerTests(const std::vector<KnipserTest> &knipserTests) {
    for (const auto &test: knipserTests) {
        tests.push_back(test);
    }
    return *this;
}

}
