//
// Created by jan on 03/08/2019.
//

#include "CliParser.h"

#include <utility>
#include "CLI/CLI.hpp"

CliParser::CliParser(int argc, char **argv) : argc(argc), argv(argv) {}

CliParseResult CliParser::parse() {
    CLI::App app{"Crayg, an awesome renderer", "Crayg"};

    std::string sceneFileName;
    app.add_option("-s,--scene", sceneFileName, "Scene file to render")->required();

    std::string imageOutputPath;
    app.add_option("-o,--output", imageOutputPath, "Path where rendered image is saved")->required();

    try {
        app.parse(argc, argv);

        return CliParseResult(CliArgs(sceneFileName, imageOutputPath), nonstd::nullopt);
    } catch (const CLI::ParseError &e) {
        return CliParseResult(nonstd::nullopt, nonstd::optional<std::string>(e.what()));
    }

}

CliArgs::CliArgs(std::string scenePath, std::string imageOutputPath)
    : scenePath(std::move(scenePath)), imageOutputPath(std::move(imageOutputPath)) {}
