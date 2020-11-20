//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_TESTRUNNER_H
#define CRAYG_TESTRUNNER_H

#include "KnipserTest.h"
#include "TestRegistry.h"
#include "TestResult.h"
#include "RunConfig.h"
#include "ExecuteTestPredicate.h"
#include <vector>

namespace knipser {

class TestRunner {
 public:
    explicit TestRunner(TestRegistry &testRegistry, RunConfig runConfig);
    std::vector<TestResult> execute();
 private:
    TestRegistry &testRegistry;
    RunConfig runConfig;
    ExecuteTestPredicate predicate;

    TestResult executeTest(const KnipserTest &test);

    TestContext createTestContext(const KnipserTest &test);
};

}

#endif //CRAYG_TESTRUNNER_H
