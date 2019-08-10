//
// Created by Jan Honsbrok on 2019-08-10.
//

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
    try{
        test.testCallback(TestContext());
        return TestResult::createPassed(test);
    }
    catch (std::exception &e){
        return TestResult::createFailed(test, e.what());
    }


}


