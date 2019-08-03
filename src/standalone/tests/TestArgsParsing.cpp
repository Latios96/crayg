//
// Created by jan on 03/08/2019.
//
#include <catch2/catch.hpp>
#include "CliParser.h"

#define ARGC_ARGV_(vector_name) \
std::vector<char*> argv_vector;\
for (const auto& arg : vector_name){\
    argv_vector.push_back((char*)arg.data());\
}\
int argc = argv_vector.size(); \
char ** argv = argv_vector.data();

TEST_CASE("shouldParseArgsValid") {
    std::vector<std::string> arguments = {"test", "-s", "/some_scene_path", "-o", "/some_image_path"};
    ARGC_ARGV_(arguments);

    CliParser cli_parser(argc, argv);
    auto result = cli_parser.parse();

    REQUIRE(result.isValid());
    REQUIRE(result.args->scenePath == "/some_scene_path");
    REQUIRE(result.args->imageOutputPath == "/some_image_path");
}

void assertHasError(const std::vector<std::string> &arguments) {
    ARGC_ARGV_(arguments);

    CliParser cli_parser(argc, argv);
    auto result = cli_parser.parse();

    REQUIRE_FALSE(result.isValid());
    REQUIRE(result.error != "");
}

TEST_CASE("invalidArgsShouldContainError") {
    std::vector<std::string> arguments = {"test"};
    assertHasError(arguments);

    arguments = {"test", "-s", "/some_scene_path"};
    assertHasError(arguments);

    arguments = {"test", "-o", "/some_image_path"};
    assertHasError(arguments);

    arguments = {"test", "-s"};
    assertHasError(arguments);

    arguments = {"test", "-o"};
    assertHasError(arguments);
}
