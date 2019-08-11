//
// Created by Jan Honsbrok on 2019-08-10.
//

#include <iostream>
#include <fmt/format.h>
#include "TestRunner.h"

TestRunner::TestRunner(const TestRegistry &testRegistry) : testRegistry(testRegistry) {}

std::vector<TestResult> TestRunner::execute() {
    std::vector<TestResult> testResults;

    for (auto &test : testRegistry.getTests()) {
        TestResult result = executeTest(test);
        testResults.push_back(result);
    }

    return testResults;
}

TestResult TestRunner::executeTest(const KnipserTest &test) {
    try {
        std::cout << fmt::format("[RUN] {}", test.name) << std::endl;
        test.testCallback(TestContext());
        std::cout << "[OK]" << std::endl;
        return TestResult::createPassed(test);
    }
    catch (std::exception &e) {
        std::cout << "[FAILED]" << std::endl;
        return TestResult::createFailed(test, e.what());
    }


}


