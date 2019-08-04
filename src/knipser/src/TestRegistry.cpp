//
// Created by jan on 03/08/2019.
//

#include <vector>
#include "TestRegistry.h"
std::shared_ptr<TestRegistry> TestRegistry::instance;

void TestRegistry::setInstance(const std::shared_ptr<TestRegistry> &instance) {
    TestRegistry::instance = instance;
}
std::shared_ptr<TestRegistry> &TestRegistry::getInstance() {
    if (!TestRegistry::instance) {
        TestRegistry::instance = std::make_shared<TestRegistry>();
    }
    return TestRegistry::instance;
}
const std::vector<KnipserTest> &TestRegistry::getTests() const {
    return tests;
}
bool TestRegistry::registerTest(const KnipserTest& knipserTest) {
    tests.push_back(knipserTest);
    return true;
}
