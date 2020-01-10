//
// Created by Jan Honsbrok on 2019-08-10.
//

#include <fmt/format.h>
#include <iostream>
#include "PlainReportGenerator.h"

void PlainReportGenerator::generateReport(std::ostream &ostream) {
    ostream << "Result:\n";
    for (auto &result : testResults) {
        ostream << getTestResultString(result) << std::endl;
    }
}

PlainReportGenerator::PlainReportGenerator(const std::vector<TestResult> &testResults) : ReportGenerator(testResults) {}

std::string PlainReportGenerator::getTestResultString(TestResult result) {
    std::string messageString;

    if (result.isPassed()) {
        messageString = "OK";
    } else if (result.isSkipped()) {
        messageString = "SKIPPED";
    } else if (result.isFailed()) {
        messageString = fmt::format("FAILED: \n{}\n", result.message);
    }
    return fmt::format("{}\t: {}",
                       result.test.name,
                       messageString);
}
