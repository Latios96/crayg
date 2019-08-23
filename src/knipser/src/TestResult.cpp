//
// Created by Jan Honsbrok on 2019-08-10.
//

#include "TestResult.h"

TestResult TestResult::createFailed(KnipserTest test, std::string message, TestContext context) {
    return TestResult(test, false, message, context);
}

TestResult TestResult::createPassed(KnipserTest test, TestContext context) {
    return TestResult(test, true, "", context);
}

TestResult::TestResult(const KnipserTest &test,
                       const bool passed,
                       const std::string &message,
                       TestContext testContext) : test(test),
                                                  passed(passed),
                                                  message(message), testContext(testContext) {}