//
// Created by Jan Honsbrok on 2019-08-10.
//

#include "TestResult.h"

TestResult TestResult::createFailed(KnipserTest test, std::string message) {
    return TestResult(test, false, message);
}

TestResult TestResult::createPassed(KnipserTest test) {
    return TestResult(test, true, "");
}

TestResult::TestResult(const KnipserTest &test, const bool passed, const std::string &message) : test(test),
                                                                                                 passed(passed),
                                                                                                 message(message) {}