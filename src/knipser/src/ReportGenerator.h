#ifndef CRAYG_REPORTGENERATOR_H
#define CRAYG_REPORTGENERATOR_H

#include <vector>
#include "TestResult.h"

namespace knipser {

class ReportGenerator {
 public:
    explicit ReportGenerator(const std::vector<TestResult> &testResults);
    virtual void generateReport(std::ostream &ostream) = 0;

 protected:
    const std::vector<TestResult> testResults;
};

}

#endif //CRAYG_REPORTGENERATOR_H
