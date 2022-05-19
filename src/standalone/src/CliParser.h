//
// Created by jan on 03/08/2019.
//

#ifndef CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
#define CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_

#include <string>
#include <utility>
#include <optional>
#include "nonstd/optional.hpp"
#include "basics/Resolution.h"
#include "CliRenderSettingsOverride.h"

namespace crayg {

struct CliArgs {
    CliArgs(std::string scenePath,
            std::string imageOutputPath,
            std::optional<std::string> cameraName,
            CliRenderSettingsOverride cliRenderSettingsOverride);
    std::string scenePath;
    std::string imageOutputPath;
    std::optional<std::string> cameraName;
    CliRenderSettingsOverride cliRenderSettingsOverride;
};

struct CliParseResult {
 public:
    CliParseResult(nonstd::optional<CliArgs> args, nonstd::optional<std::string> error)
        : args(std::move(args)), error(std::move(error)) {}

    nonstd::optional<CliArgs> args;
    nonstd::optional<std::string> error;

    bool isValid() const {
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

}

#endif //CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
