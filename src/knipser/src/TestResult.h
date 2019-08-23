//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_TESTRESULT_H
#define CRAYG_TESTRESULT_H


#include "KnipserTest.h"

struct TestResult {
public:
    TestResult(const KnipserTest &test,
               const bool passed,
               const std::string &message,
               TestContext testContext);
    // todo store context test was ran with
    static TestResult createFailed(KnipserTest test, std::string message, TestContext context);
    static TestResult createPassed(KnipserTest test, TestContext context);
    const KnipserTest test;
    const bool passed;
    const std::string message;
    const TestContext testContext;
};


#endif //CRAYG_TESTRESULT_H
