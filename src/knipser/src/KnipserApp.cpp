#include <KnipserApp.h>
#include "PlainReportGenerator.h"
#include "TestPatternStringParser.h"

namespace knipser {

ExitMessage KnipserApp::execute() {
    CLI::App app {"Integration testing framework for projects with image output", "Knipser"};

    std::string outputFolder;
    app.add_option("-o,--output", outputFolder, "Path where test results are saved")->required();

    std::string referenceFolder;
    app.add_option("-r,--reference", referenceFolder, "Path where reference images are stored")->required();

    std::string testPatternString;
    app.add_option("-t,--test-patterns", testPatternString, "Comma-seperated list of test name pattern to ne executed");

    try {
        (app).parse((argc), (argv));
    } catch (const CLI::ParseError &e) {
        return {1, e.what()};
    }

    TestPatternStringParser parser(testPatternString);
    const std::vector<TestPattern> testPatterns = parser.parse();

    RunConfig runConfig(outputFolder, referenceFolder, testPatterns);

    TestRunner testRunner(testRegistry, runConfig);
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
    int skippedCount = 0;

    for (auto &testResult : testResults) {
        if (testResult.isPassed()) {
            passedCount++;
        } else if (testResult.isFailed()) {
            failedCount++;
        } else {
            skippedCount++;
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
        message = fmt::format("\n{}\nRan {} tests, {} passed, {} skipped and {} failed",
                              ss.str(),
                              testResults.size(),
                              passedCount,
                              skippedCount,
                              failedCount);

    return {exitCode, message};
}

}
