//
// Created by Jan Honsbrok on 2019-08-10.
//

#ifndef CRAYG_PLAINREPORTGENERATOR_H
#define CRAYG_PLAINREPORTGENERATOR_H


#include "ReportGenerator.h"

class PlainReportGenerator : public ReportGenerator {
public:
    PlainReportGenerator(const std::vector<TestResult> &testResults);

    void generateReport(std::ostream &ostream) override;

private:
    std::string getTestResultString(TestResult result);
};


#endif //CRAYG_PLAINREPORTGENERATOR_H
