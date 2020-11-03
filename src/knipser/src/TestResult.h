//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_TESTRESULT_H
#define CRAYG_TESTRESULT_H

#include "KnipserTest.h"
enum TestResultState {
    FAILED, PASSED, SKIPPED
};
struct TestResult {
 public:
    TestResult(const KnipserTest &test,
               const TestResultState state,
               const std::string &message,
               TestContext testContext);

    static TestResult createFailed(KnipserTest test, std::string message, TestContext context);
    static TestResult createPassed(KnipserTest test, TestContext context);
    static TestResult createSkipped(KnipserTest test, TestContext context);

    const KnipserTest test;
    TestResultState state;
    const std::string message;
    const TestContext testContext;

    bool isFailed() const;
    bool isPassed() const;
    bool isSkipped() const;
};

#endif //CRAYG_TESTRESULT_H
