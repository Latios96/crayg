//
// Created by jan on 23/08/2019.
//

#ifndef CRAYG_SRC_KNIPSER_SRC_KNIPSERAPP_H_
#define CRAYG_SRC_KNIPSER_SRC_KNIPSERAPP_H_

#include "TestRunner.h"
#include <string>
#include <utility>
#include <fmt/format.h>
#include "CLI/CLI.hpp"

#define KNIPSER_MAIN(testRegistry) KnipserApp app(argc, argv, testRegistry);ExitMessage exitMessage = app.execute();std::cout << exitMessage.message << std::endl;return exitMessage.exitCode

struct ExitMessage {
 public:
    ExitMessage(int exitCode, std::string message) : exitCode(exitCode), message(std::move(message)) {}
    int exitCode;
    std::string message;
};

class KnipserApp {
 public:
    KnipserApp(int argc, char **argv, TestRegistry &testRegistry) : argc(argc), argv(argv), testRegistry(testRegistry) {}

    ExitMessage execute();

 private:
    ExitMessage createExitMessage(const std::vector<TestResult> &testResults);

    int argc;
    char **argv;
    ExitMessage exitMessageFromTestResults(const std::vector<TestResult> &testResults) const;
    TestRegistry &testRegistry;
};

#endif //CRAYG_SRC_KNIPSER_SRC_KNIPSERAPP_H_
