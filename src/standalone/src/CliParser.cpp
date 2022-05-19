//
// Created by jan on 03/08/2019.
//

#include "CliParser.h"

#include "CLI/CLI.hpp"

namespace crayg {

CliParser::CliParser(int argc, char **argv) : argc(argc), argv(argv) {}

CliParseResult CliParser::parse() {
    CLI::App app {"Crayg, an awesome renderer", "Crayg"};

    std::string sceneFileName;
    app.add_option("-s,--scene", sceneFileName, "Scene file to render")->required();

    std::string imageOutputPath;
    app.add_option("-o,--output", imageOutputPath, "Path where rendered image is saved")->required();

    std::string cameraName;
    app.add_option("--camera",
                   cameraName,
                   "Name of the camera to render. Defaulting to the first camera found in the scene");

    std::string resolution;
    app.add_option("--resolution", resolution, "Override resolution to render, format: 1280x720");

    int maxSamples = 0;
    app.add_option("--maxSamples", maxSamples, "Override max samples");

    try {
        app.parse(argc, argv);

        CliRenderSettingsOverride renderSettingsOverride;
        if (!resolution.empty()) {
            renderSettingsOverride.resolution = Resolution::parse(resolution);
        }
        if (maxSamples) {
            renderSettingsOverride.maxSamples = maxSamples;
        }

        return CliParseResult(CliArgs(sceneFileName,
                                      imageOutputPath,
                                      !cameraName.empty() ? std::make_optional(cameraName) : std::nullopt,
                                      renderSettingsOverride), std::nullopt);
    } catch (const std::runtime_error &e) {
        return CliParseResult(std::nullopt, std::optional<std::string>(e.what()));
    }

}

CliArgs::CliArgs(std::string scenePath,
                 std::string imageOutputPath,
                 std::optional<std::string> cameraName,
                 CliRenderSettingsOverride cliRenderSettingsOverride)
    : scenePath(scenePath), imageOutputPath(imageOutputPath), cameraName(cameraName),
      cliRenderSettingsOverride(cliRenderSettingsOverride) {

}
}