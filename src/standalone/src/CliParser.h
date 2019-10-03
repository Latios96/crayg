//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
#define CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_

#include <string>
#include <utility>
#include "nonstd/optional.hpp"

struct CliArgs {
    CliArgs(std::string scenePath, std::string imageOutputPath);
    std::string scenePath;
    std::string imageOutputPath;
};

struct CliParseResult {
 public:
    CliParseResult(nonstd::optional<CliArgs> args, nonstd::optional<std::string> error)
        : args(std::move(args)), error(std::move(error)) {}

    nonstd::optional<CliArgs> args;
    nonstd::optional<std::string> error;

    bool isValid() {
        return !error && args;
    }
};

class CliParser {
 public:
    CliParser(int argc, char **argv);

    CliParseResult parse();

 private:
    int argc;
    char **argv;
};

#endif //CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
