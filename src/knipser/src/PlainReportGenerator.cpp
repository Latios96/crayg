//
// Created by Jan Honsbrok on 2019-08-10.
//

#include <fmt/format.h>
#include <iostream>
#include "PlainReportGenerator.h"

void PlainReportGenerator::generateReport(std::ostream &ostream) {
    for (auto &result : testResults) {
        ostream << getTestResultString(result) << std::endl;
    }
}

PlainReportGenerator::PlainReportGenerator(const std::vector<TestResult> &testResults) : ReportGenerator(testResults) {}

std::string PlainReportGenerator::getTestResultString(TestResult result) {
    return fmt::format("{}\t: {}",
                       result.test.name,
                       result.passed ? "OK" : fmt::format("FAILED: \n{}\n", result.message));
}
