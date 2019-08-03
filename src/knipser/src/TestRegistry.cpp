//
// Created by jan on 03/08/2019.
//

#include <vector>
#include "TestRegistry.h"
std::shared_ptr<TestRegistry> TestRegistry::instance;

void TestRegistry::setInstance(const std::shared_ptr<TestRegistry> &instance) {
    TestRegistry::instance = instance;
}
bool TestRegistry::registerTest(std::string name, std::function<void(TestContext)> testCallback) {
    tests.emplace_back(name, testCallback);
    return true;
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
