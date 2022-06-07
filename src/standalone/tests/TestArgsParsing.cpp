//
// Created by jan on 03/08/2019.
//
#include <catch2/catch.hpp>
#include "CliParser.h"

namespace crayg {

#define ARGC_ARGV_(vector_name) \
std::vector<char*> argv_vector;\
for (const auto& arg : vector_name){\
    argv_vector.push_back((char*)arg.data());\
}\
int argc = argv_vector.size(); \
char ** argv = argv_vector.data();

TEST_CASE("shouldParseArgsValid") {
    std::vector<std::string> arguments = {"tests", "-s", "/some_scene_path", "-o", "/some_image_path"};
    ARGC_ARGV_(arguments);

    CliParser cli_parser("executable_name", argc, argv);
    auto result = cli_parser.parse();

    REQUIRE(result.isValid());
    REQUIRE(result.args->scenePath == "/some_scene_path");
    REQUIRE(result.args->imageOutputPath == "/some_image_path");
}

TEST_CASE("shouldParseOptionalArgs") {
    std::vector<std::string> arguments =
        {"tests", "-s", "/some_scene_path", "-o", "/some_image_path", "--camera", "/usdCamera", "--resolution",
         "1280x720", "--maxSamples", "8"};
    ARGC_ARGV_(arguments);

    CliParser cli_parser("executable_name", argc, argv);
    auto result = cli_parser.parse();

    REQUIRE(result.isValid());
    REQUIRE(result.args->scenePath == "/some_scene_path");
    REQUIRE(result.args->imageOutputPath == "/some_image_path");
    REQUIRE(result.args->cameraName == "/usdCamera");
    REQUIRE(result.args->cliRenderSettingsOverride.resolution == Resolution(1280, 720));
    REQUIRE(result.args->cliRenderSettingsOverride.maxSamples == 8);
}

void assertHasError(const std::vector<std::string> &arguments) {
    ARGC_ARGV_(arguments);

    CliParser cli_parser("executable_name", argc, argv);
    auto result = cli_parser.parse();

    REQUIRE_FALSE(result.isValid());
    REQUIRE(result.error != "");
}

TEST_CASE("invalidArgsShouldContainError") {
    std::vector<std::string> arguments = {"tests"};
    assertHasError(arguments);

    arguments = {"tests", "-s", "/some_scene_path"};
    assertHasError(arguments);

    arguments = {"tests", "-o", "/some_image_path"};
    assertHasError(arguments);

    arguments = {"tests", "-s"};
    assertHasError(arguments);

    arguments = {"tests", "-o"};
    assertHasError(arguments);

    arguments = {"tests", "-s", "/some_scene_path", "-o", "/some_image_path", "--resolution", "8"};
    assertHasError(arguments);
}

}