//
// Created by Jan Honsbrok on 2019-08-10.
//

#include "TestResult.h"

namespace knipser {

TestResult TestResult::createFailed(KnipserTest test, std::string message, TestContext context) {
    return TestResult(test, TestResultState::FAILED, message, context);
}

TestResult TestResult::createPassed(KnipserTest test, TestContext context) {
    return TestResult(test, TestResultState::PASSED, "", context);
}

TestResult TestResult::createSkipped(KnipserTest test, TestContext context) {
    return TestResult(test, TestResultState::SKIPPED, "", context);
}

bool TestResult::isFailed() const {
    return state == TestResultState::FAILED;
}
bool TestResult::isPassed() const {
    return state == TestResultState::PASSED;
}
bool TestResult::isSkipped() const {
    return state == TestResultState::SKIPPED;
}

TestResult::TestResult(const KnipserTest &test,
                       const TestResultState state,
                       const std::string &message,
                       TestContext testContext) : test(test),
                                                  state(state),
                                                  message(message), testContext(testContext) {}

}