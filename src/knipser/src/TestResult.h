//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_TESTRESULT_H
#define CRAYG_TESTRESULT_H


#include "KnipserTest.h"

struct TestResult {
public:
    TestResult(const KnipserTest &test, bool passed, const std::string &message);

    static TestResult createFailed(KnipserTest test, std::string message);
    static TestResult createPassed(KnipserTest test);
    const KnipserTest test;
    const bool passed;
    const std::string message;
};


#endif //CRAYG_TESTRESULT_H
