//
// Created by jan on 23/08/2019.
//
#include <KnipserApp.h>
#include "PlainReportGenerator.h"

ExitMessage KnipserApp::execute() {
    CLI::App app{"Integration testing framework for projects with image output", "Knipser"};

    std::string outputFolder;
    app.add_option("-o,--output", outputFolder, "Path where test results are saved")->required();

    std::string referenceFolder;
    app.add_option("-r,--reference", referenceFolder, "Path where reference images are stored")->required();

    try {
        (app).parse((argc), (argv));
    } catch (const CLI::ParseError &e) {
        return {1, e.what()};
    }

    RunConfig runConfig(outputFolder, referenceFolder);

    TestRunner testRunner(*TestRegistry::getInstance(), runConfig);
    const std::vector<TestResult> testResults = testRunner.execute();

    return createExitMessage(testResults);
}
ExitMessage KnipserApp::createExitMessage(const std::vector<TestResult> &testResults) {
    if (testResults.empty()) {
        return {1, "No tests found!"};
    }
    return exitMessageFromTestResults(testResults);

}
ExitMessage KnipserApp::exitMessageFromTestResults(const std::vector<TestResult> &testResults) const {
    int passedCount = 0;
    int failedCount = 0;

    for (auto &testResult : testResults) {
        if (testResult.passed) {
            passedCount++;
        } else {
            failedCount++;
        }
    }

    int exitCode = 0;
    if (failedCount > 0) {
        exitCode = 1;
    }
    PlainReportGenerator plainReportGenerator(testResults);
    std::stringstream ss;
    plainReportGenerator.generateReport(ss);

    std::string
        message = fmt::format("\n{}\nRan {} tests, {} passed and {} failed",
                              ss.str(),
                              testResults.size(),
                              passedCount,
                              failedCount);

    return {exitCode, message};
}
