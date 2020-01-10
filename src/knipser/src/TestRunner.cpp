//
// Created by Jan Honsbrok on 2019-08-10.
//

#include <iostream>
#include <fmt/format.h>
#include "TestRunner.h"
#include "ExecuteTestPredicate.h"
#include <boost/filesystem.hpp>
#include <functional>
#include <utility>

TestRunner::TestRunner(TestRegistry &testRegistry, RunConfig runConfig) : testRegistry(testRegistry),
                                                                          runConfig(std::move(runConfig)) {}

std::vector<TestResult> TestRunner::execute() {
    std::vector<TestResult> testResults;
    ExecuteTestPredicate predicate(runConfig.testPatterns);

    for (auto &test : testRegistry.getTests()) {
        if (predicate.shouldExecute(test)) {
            TestResult result = executeTest(test);
            testResults.push_back(result);
        }
    }

    return testResults;
}

TestResult TestRunner::executeTest(const KnipserTest &test) {
    TestContext testContext = createTestContext(test);
    try {
        std::cout << fmt::format("[RUN] {}", test.name) << std::endl;

        test.testCallback(testContext);

        std::cout << "[OK]" << std::endl;
        return TestResult::createPassed(test, testContext);
    }
    catch (std::exception &e) {
        std::cout << fmt::format("[FAILED]:\n {}", e.what()) << std::endl;
        return TestResult::createFailed(test, e.what(), testContext);
    }

}

TestContext TestRunner::createTestContext(const KnipserTest &test) {
    auto testOutputFolder = boost::filesystem::path(runConfig.outputFolder).append(test.name);
    auto testReferenceFolder = boost::filesystem::path(runConfig.referenceFolder).append(test.name);

    boost::filesystem::create_directories(testOutputFolder);

    return TestContext(testOutputFolder.string(), testReferenceFolder.string());
}


