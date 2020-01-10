//
// Created by Jan Honsbrok on 2019-08-10.
//

#include <fmt/format.h>
#include <iostream>
#include "PlainReportGenerator.h"

void PlainReportGenerator::generateReport(std::ostream &ostream) {
    ostream << "Result:\n";
    for (auto &result : testResults) {
        ostream << getTestResultString(result, getMaxNameLength()) << std::endl;
    }
}

PlainReportGenerator::PlainReportGenerator(const std::vector<TestResult> &testResults) : ReportGenerator(testResults) {}

unsigned long PlainReportGenerator::getMaxNameLength() const {
    return std::max_element(testResults.begin(), testResults.end(), [](const TestResult &a, const TestResult &b) {
        return a.test.name.length() < b.test.name.length();
    })->test.name.length();
}

std::string PlainReportGenerator::getTestResultString(const TestResult &result, unsigned long maxNameLength) const {
    std::string messageString;

    if (result.isPassed()) {
        messageString = "OK";
    } else if (result.isSkipped()) {
        messageString = "SKIPPED";
    } else if (result.isFailed()) {
        messageString = fmt::format("FAILED: \n{}\n", result.message);
    }

    unsigned long missingSpacesCount = maxNameLength - result.test.name.length();

    return fmt::format("{}{} : {}",
                       result.test.name,
                       std::string(missingSpacesCount,' '),
                       messageString);
}

