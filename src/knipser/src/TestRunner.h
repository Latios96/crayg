//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_TESTRUNNER_H
#define CRAYG_TESTRUNNER_H

#include "KnipserTest.h"
#include "TestRegistry.h"
#include "TestResult.h"
#include <vector>



class TestRunner {
public:
    explicit TestRunner(const TestRegistry &testRegistry);
    std::vector<TestResult> execute();
private:
    TestRegistry testRegistry;

    TestResult executeTest(const KnipserTest &test);
};


#endif //CRAYG_TESTRUNNER_H
