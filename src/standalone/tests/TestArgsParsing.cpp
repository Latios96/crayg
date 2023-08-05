#include "CliParser.h"
#include <catch2/catch.hpp>

namespace crayg {

#define ARGC_ARGV_(vector_name)                                                                                        \
    std::vector<char *> argv_vector;                                                                                   \
    for (const auto &arg : vector_name) {                                                                              \
        argv_vector.push_back((char *)arg.data());                                                                     \
    }                                                                                                                  \
    int argc = static_cast<int>(argv_vector.size());                                                                   \
    char **argv = argv_vector.data();

void assertHasError(const std::vector<std::string> &arguments) {
    ARGC_ARGV_(arguments);

    CliParser cli_parser("executable_name", argc, argv);
    auto result = cli_parser.parse();

    REQUIRE_FALSE(result.isValid());
    REQUIRE(result.error != "");
}

TEST_CASE("CliParser::parse") {
    SECTION("should parse args valid") {
        std::vector<std::string> arguments = {"tests", "-s", "/some_scene_path", "-o", "/some_image_path"};
        ARGC_ARGV_(arguments);

        CliParser cli_parser("executable_name", argc, argv);
        auto result = cli_parser.parse();

        REQUIRE(result.isValid());
        REQUIRE(result.args->scenePath == "/some_scene_path");
        REQUIRE(result.args->imageOutputPath == "/some_image_path");
    }

    SECTION("should parse optional args") {
        std::vector<std::string> arguments = {"tests",
                                              "-s",
                                              "/some_scene_path",
                                              "-o",
                                              "/some_image_path",
                                              "--camera",
                                              "/usdCamera",
                                              "--resolution",
                                              "1280x720",
                                              "--maxSamples",
                                              "8",
                                              "--intersector",
                                              "EMBREE",
                                              "--bucketSamplerType",
                                              "UNIFORM",
                                              "--adaptiveMaxError",
                                              "0.1",
                                              "--samplesPerAdaptivePass",
                                              "16",
                                              "--variantSelection",
                                              "/Camera/Camera:camera_lens=realistic_realistic_canon_50mm",
                                              "--variantSelection",
                                              "/Camera/OtherCamera:other_camera_lens=realistic_realistic_canon_50mm"

        };
        ARGC_ARGV_(arguments);

        CliParser cli_parser("executable_name", argc, argv);
        auto result = cli_parser.parse();

        REQUIRE(result.isValid());
        REQUIRE(result.args->scenePath == "/some_scene_path");
        REQUIRE(result.args->imageOutputPath == "/some_image_path");
        REQUIRE(result.args->cameraName == "/usdCamera");
        REQUIRE(result.args->cliRenderSettingsOverride.resolution == Resolution(1280, 720));
        REQUIRE(result.args->cliRenderSettingsOverride.maxSamples == 8);
        REQUIRE(result.args->cliRenderSettingsOverride.intersectorType == IntersectorType::EMBREE);
        REQUIRE(result.args->cliRenderSettingsOverride.bucketSamplerType == BucketSamplerType::UNIFORM);
        REQUIRE(result.args->cliRenderSettingsOverride.adaptiveMaxError == 0.1f);
        REQUIRE(result.args->cliRenderSettingsOverride.samplesPerAdaptivePass == 16);
        REQUIRE(result.args->variantSelections[0] ==
                SceneReaderVariantSelection("/Camera/Camera", "camera_lens", "realistic_realistic_canon_50mm"));
        REQUIRE(result.args->variantSelections[1] == SceneReaderVariantSelection("/Camera/OtherCamera",
                                                                                 "other_camera_lens",
                                                                                 "realistic_realistic_canon_50mm"));
    }

    SECTION("invalid args should contain error") {
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

        arguments = {"tests", "-s", "/some_scene_path", "-o", "/some_image_path", "--variantSelection", "8"};
        assertHasError(arguments);
    }
}

}