//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_REPORTGENERATOR_H
#define CRAYG_REPORTGENERATOR_H

#include <vector>
#include "TestResult.h"

class ReportGenerator {
public:
    explicit ReportGenerator(const std::vector<TestResult> &testResults);
    virtual void generateReport(std::ostream &ostream) = 0;

protected:
    const std::vector<TestResult> testResults;
};


#endif //CRAYG_REPORTGENERATOR_H
