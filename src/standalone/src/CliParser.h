#ifndef CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
#define CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_

#include "CliRenderSettingsOverride.h"
#include "basics/Resolution.h"
#include <optional>
#include <string>
#include <utility>

namespace crayg {

struct CliArgs {
    CliArgs(std::string scenePath, std::string imageOutputPath, std::optional<std::string> cameraName,
            CliRenderSettingsOverride cliRenderSettingsOverride);
    std::string scenePath;
    std::string imageOutputPath;
    std::optional<std::string> cameraName;
    CliRenderSettingsOverride cliRenderSettingsOverride;
};

struct CliParseResult {
  public:
    CliParseResult(std::optional<CliArgs> args, std::optional<std::string> error)
        : args(std::move(args)), error(std::move(error)) {
    }

    std::optional<CliArgs> args;
    std::optional<std::string> error;

    bool isValid() const {
        return !error && args;
    }
};

class CliParser {
  public:
    CliParser(const std::string &executableName, int argc, char **argv);

    CliParseResult parse();

  private:
    int argc;
    char **argv;
    std::string executableName;
};

}

#endif // CRAYG_SRC_STANDALONE_SRC_CLI_PARSER_H_
