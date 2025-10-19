#pragma once

#include "CliRenderSettingsOverride.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/scene/io/read/SceneReader.h"
#include <optional>
#include <string>
#include <utility>

namespace crayg {

struct CliArgs {
    CliArgs(std::string scenePath, std::string imageOutputPath, std::optional<std::string> cameraName,
            CliRenderSettingsOverride cliRenderSettingsOverride,
            const std::vector<SceneReaderVariantSelection> &variantSelections);
    std::string scenePath;
    std::string imageOutputPath;
    std::optional<std::string> cameraName;
    std::vector<SceneReaderVariantSelection> variantSelections;
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
